#include <string>
#include <vector>

struct FlagsHandler
{
    std::string base_path;
    std::string log_path;
    std::string path_folder;

    void parse(const std::vector<std::string>& argv);
};