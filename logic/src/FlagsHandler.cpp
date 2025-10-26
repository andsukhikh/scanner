#include "FlagsHandler.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <algorithm>
#include <exception>
#include <filesystem>


void FlagsHandler::parse(const std::vector<std::string>& argv)
{
    auto get_flag_value = [&](std::string_view flag) -> std::string
        {
            auto it = std::find(argv.begin(), argv.end(), flag);

            if (it != argv.end() && (it + 1) != argv.end()) 
            {
                if ((it + 1) -> find("--") == std::string::npos)
                    return *(it + 1);
            }
            return {};
        };

    auto handle_path = [](std::filesystem::path path, const std::string& default_filename = "") -> std::filesystem::path
        {
            if (path.empty())
            {
                std::cout << "Note: If the " + default_filename + " path is not specified, it will be created in the current directory" << std::endl;
                path = (std::filesystem::current_path() / default_filename).string();

                return path;
            }

            if(default_filename == "" && !std::filesystem::is_directory(path))
            {
                throw std::runtime_error("The directory with the filename is specified, you only need to specify the directory scanning");
            }

            if (default_filename != "" && !std::filesystem::is_regular_file(path))
            {
                throw std::runtime_error("The " + path.string() + " directory specified without filename or this file don't exist in the directory");
            }

            return path;
        };

    base_path = handle_path(get_flag_value("--base"), "base.csv");
    log_path = handle_path(get_flag_value("--log"), "log.txt");
    path_folder = handle_path(get_flag_value("--path"));

}