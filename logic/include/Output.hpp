#include <chrono>
#include <thread>
#include <mutex>
#include <fstream>
#include <string_view>
#include <chrono>
#include <filesystem>


class Scanner
{
    std::atomic<std::size_t> number_of_checked_files_{0};
    std::atomic<std::size_t> number_of_viral_files_{0};
    std::atomic<std::size_t> number_of_error_files_{0};

    std::chrono::time_point<std::chrono::steady_clock> initial_time;

public:
    ~Scanner(); 
    Scanner();

public:
    void plus_error_file();
    void plus_viral_file();
    void plus_checked_file();
};


class Logger
{
    std::fstream log_file_;
    std::mutex mutex_;
public:
    static Logger& getInstance();

    void set_log_directory_to(std::filesystem::path path);

    void log(std::filesystem::path path, std::string_view hash, std::string_view verdict);

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

