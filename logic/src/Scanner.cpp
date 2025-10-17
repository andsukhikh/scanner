#include "Scanner.hpp"
#include "Output.hpp"

#include <openssl/md5.h>


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <string_view>
#include <mutex>
#include <thread>
#include <optional>
#include <deque>
#include <chrono>
#include <exception>


Bases::Bases(const std::filesystem::path& base_path)
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

        bases_[hash] = verdict;
    }
}

std::string& Bases::operator[] (const std::string& hash)
{
    return bases_[hash];
}

std::optional<std::string> Bases::match(const std::string& verifiable_hash)
{
    auto it = bases_.find(verifiable_hash);
    if (it != bases_.end())
        return it -> second;

    return std::nullopt;
}

Scanner::Scanner(std::string_view path_to_base, std::string_view folder_path)
        : bases_(path_to_base)
        , path_to_directory_for_scanning_(folder_path)
    {}

void Scanner::start()
{
    Threads threads;
    ScannerReport scanner_report;

    for (auto&& dir_enrty : std::filesystem::recursive_directory_iterator(path_to_directory_for_scanning_))
    {
        if(!dir_enrty.is_directory())
        {
            const auto logic = [this, &scanner_report, dir_enrty]()
                {
                    const auto verifiable_file_hash = md5(dir_enrty.path());
                    const auto verdict = bases_.match(verifiable_file_hash);

                    scanner_report.plus_checked_file();
                    if (verifiable_file_hash.empty())
                    {
                        scanner_report.plus_error_file();
                    }

                    if (verdict)
                    {
                        Logger::get_instance().log(dir_enrty.path(), verifiable_file_hash, verdict.value());
                        scanner_report.plus_viral_file();
                    }
                };
            threads.take_task(logic);
        }
    }
}    

std::string Scanner::md5(std::filesystem::path file_path)
{
    std::fstream file(file_path, std::ios::binary | std::ios::in);
    if (file.is_open())
    {
        auto file_size = std::filesystem::file_size(file_path);

        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(file_size);

        file.read(buffer.get(), file_size);
        file.close();

        unsigned char result[MD5_DIGEST_LENGTH];
        MD5(reinterpret_cast<const unsigned char*>(buffer.get()), file_size, result);

        std::ostringstream oss;
        for (std::size_t i = 0; i < MD5_DIGEST_LENGTH; ++i)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(result[i]);
        }
        return oss.str();
    }
    return {};
}

Threads::Threads()
    : MAX_THREADS{std::max(1u, std::thread::hardware_concurrency()) }
{}

template<typename Func>
void Threads::take_task(Func&& func)
{
    std::thread new_thread(func);
    std::thread old_thread;

    threads_.emplace_back(std::move(new_thread));

    if (threads_.size() >= MAX_THREADS)
    {
        old_thread = std::move(threads_.front());
        threads_.pop_front();
    }

    if (old_thread.joinable())
        old_thread.join();
}

Threads::~Threads()
{
    for (auto&& thread : threads_)
        if (thread.joinable())
            thread.join();
}