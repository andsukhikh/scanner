#include "Utility.hpp"
#include "Output.hpp"

#include <openssl/md5.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <format>
#include <filesystem>
#include <string_view>
#include <mutex>
#include <thread>
#include <optional>
#include <deque>
#include <chrono>
#include <algorithm>
#include <exception>


BaseHash::BaseHash(const std::filesystem::path& base_path)
{
    std::fstream baseFile(base_path, std::ios::in);

    if(!baseFile.is_open())
    {
        throw std::runtime_error("Failed to open file in base");
    }

    for (std::string line; getline(baseFile, line);)
    {
        auto separator_mark = line.find(';');

        std::string verdict = line.substr(separator_mark + 1, std::string::npos);
        std::string hash = line.substr(0, separator_mark);

        base_hash_[hash] = verdict;
    }
}

std::string& BaseHash::operator[] (const std::string& hash)
{
    return base_hash_[hash];
}

std::optional<std::string> BaseHash::match(const std::string& verifiable_hash)
{
    if (base_hash_.contains(verifiable_hash))
        return base_hash_[verifiable_hash];

    return std::nullopt;
}



Utility::Utility(std::string_view path_to_base, std::string_view folder_path)
        : base_hash_(path_to_base)
        , path_to_directory_for_scanning_(folder_path)
    {}

void Utility::start()
{
    auto MAX_THREADS = std::thread::hardware_concurrency();
    std::deque<std::thread> threads_pool;
    Scanner scanner;

    for (auto&& dir_enrty : std::filesystem::recursive_directory_iterator(path_to_directory_for_scanning_))
    {
        const auto logic = [this, &scanner, dir_enrty]()
            {
                const auto verifiable_file_hash = md5(dir_enrty.path());
                const auto verdict = base_hash_.match(verifiable_file_hash);

                scanner.plus_checked_file();
                if (verifiable_file_hash.empty())
                {
                    scanner.plus_error_file();
                }

                if (verdict)
                {
                    Logger::getInstance().log(dir_enrty.path(), verifiable_file_hash, verdict.value());
                    scanner.plus_viral_file();
                }

            };

        if (threads_pool.size() >= MAX_THREADS)
        {
            threads_pool.front().join();
            threads_pool.pop_front();
        }

        threads_pool.emplace_back(logic);
    }

    for (auto&& thread : threads_pool)
        if (thread.joinable())
            thread.join();
}    

std::string Utility:: md5(std::filesystem::path file_path)
{
    std::fstream file(file_path, std::ios::binary | std::ios::ate | std::ios::in);
    if (file.is_open())
    {
        auto fileSize = std::filesystem::file_size(file_path);

        std::vector<char> buffer(fileSize);
        file.read(buffer.data(), fileSize);

        unsigned char result[MD5_DIGEST_LENGTH];
        MD5(reinterpret_cast<unsigned char*>(buffer.data()), fileSize, result);

        std::ostringstream oss;
        for (std::size_t i = 0; i < MD5_DIGEST_LENGTH; ++i)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(result[i]);
        }
        return oss.str();
    }
    return {};
}