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

    auto handle_path = [](std::string& path, const std::string& default_filename = "")
        {
            if (path.empty())
            {
                std::cout << "Note: If the " + default_filename + " path is not specified, it will be created in the current directory" << std::endl;
                path = (std::filesystem::current_path() / default_filename).string();
            }

            if(default_filename == "" && !std::filesystem::is_directory(path))
            {
                throw std::runtime_error("The directory with the filename is specified, you only need to specify the directory scanning");
            }

            if (default_filename != "" && !std::filesystem::is_regular_file(path))
            {
                throw std::runtime_error("The " + path + " directory specified without filename");
            }

        };

    base_path = get_flag_value("--base");
    log_path = get_flag_value("--log");
    path_folder = get_flag_value("--path");

    handle_path(base_path, "base.csv");
    handle_path(log_path, "log.txt");
    handle_path(path_folder);

}


