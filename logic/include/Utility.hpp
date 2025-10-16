#include <unordered_map>
#include <string>
#include <filesystem>
#include <optional>


class BaseHash
{
    std::unordered_map<std::string, std::string> base_hash_;
public:
    BaseHash(const std::filesystem::path& base_path);

    std::string& operator[] (const std::string& hash);
    std::optional<std::string> match(const std::string& verifiable_hash);
};

class Utility
{
    BaseHash base_hash_;
    std::filesystem::path path_to_directory_for_scanning_;
public:
    Utility(std::string_view path_to_base, std::string_view folder_path);
    void start();
    std::string md5(std::filesystem::path file_path);

};