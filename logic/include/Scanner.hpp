#include <unordered_map>
#include <string>
#include <filesystem>
#include <optional>
#include <deque>
#include <thread>
#include <mutex>


class Bases
{
    std::unordered_map<std::string, std::string> bases_;
public:
    Bases(const std::filesystem::path& base_path);

    std::string& operator[] (const std::string& hash);
    std::optional<std::string> match(const std::string& verifiable_hash);
};

class Scanner
{
    Bases bases_;
    std::filesystem::path path_to_directory_for_scanning_;
public:
    Scanner(std::string_view path_to_base, std::string_view folder_path);
    void start();
    std::string md5(std::filesystem::path file_path);

};

class Threads
{
    std::deque<std::thread> threads_;
    
    const unsigned int MAX_THREADS;
public:
    Threads();
    ~Threads();
    template<typename Func>
    void take_task(Func&& func);
};