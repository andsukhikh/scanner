#include "FlagsHandler.hpp"

#include <iostream>
#include <exception>
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


void FlagsHandler::parse(const std::vector<std::string>& argv)
{
    auto get_flag_value = [&](const std::string& flag) -> std::string 
    {
        auto it = std::find(argv.begin(), argv.end(), flag);

        if (it != argv.end() && (it + 1) != argv.end()) 
        {
            if ((it + 1)->find("--") == std::string::npos)
                return *(it + 1);
        }
        return {};
    };

    base_path = get_flag_value("--base");
    if (base_path.empty())
    {
        throw std::runtime_error("Missing --base startup flag or its value");
    }

    log_path = get_flag_value("--log");
    if (log_path.empty()) 
    {
        std::cout << "Note: If the log path is not specified, it will be created in the current directory" << std::endl;
        log_path = std::filesystem::current_path().string() + "\\log.txt";
    }

    path_folder = get_flag_value("--path");
    if (path_folder.empty()) 
    {
        std::cout << "Note: If the path folder is not specified, it will scan in the current directory" << std::endl;
        path_folder = std::filesystem::current_path().string();
    }
}


