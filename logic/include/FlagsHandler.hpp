#include <string>
#include <vector>
#include <filesystem>

struct FlagsHandler
{
    std::filesystem::path base_path;
    std::filesystem::path log_path;
    std::filesystem::path path_folder;

    void parse(const std::vector<std::string>& argv);
};