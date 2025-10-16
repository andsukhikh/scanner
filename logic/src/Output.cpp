#include "Output.hpp"

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


Scanner::~Scanner()
{
    auto end_time = std::chrono::steady_clock::now();
    auto exec_time = duration_cast<std::chrono::milliseconds>(end_time - initial_time).count();

    std::cout << std::format("Total checked files : {}\n", number_of_checked_files_.load());
    std::cout << std::format("Viruses detected : {}\n", number_of_viral_files_.load());
    std::cout << std::format("Analysis errors : {}\n", number_of_error_files_.load());
    std::cout << std::format("Execution time : {} ms\n", exec_time);
}

Scanner::Scanner() 
        : initial_time(std::chrono::steady_clock::now())
    {}

void Scanner::plus_error_file()
{
    ++number_of_error_files_;
}

void Scanner::plus_viral_file()
{
    ++number_of_viral_files_;
}

void Scanner::plus_checked_file()
{
    ++number_of_checked_files_;
}

Logger::Logger() {}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::set_log_directory_to(std::filesystem::path path)
{
    std::lock_guard lock(mutex_);

    log_file_.open(path, std::ios::out | std::ios::trunc);

    if(!log_file_.is_open())
    {
        throw std::runtime_error("Failed to open file for log");
    }
}

void Logger::log(std::filesystem::path path, std::string_view hash, std::string_view verdict)
{
    std::lock_guard lock(mutex_);
    log_file_ << std::format("Path of the detected virus : {}\n", path.string());
    log_file_ << std::format("Hash                       : {}\n", hash);
    log_file_ << std::format("Verdict                    : {}\n", verdict);
    log_file_ << "\n";
}


