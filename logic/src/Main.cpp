#include <iostream>

#include "FlagsHandler.hpp"
#include "Output.hpp"
#include "Utility.hpp"

int main(int argc, char* argv[])
{
    FlagsHandler flags_handler;
    try
    {
        flags_handler.parse(std::vector<std::string>(argv + 1, argv + argc));
    }
    catch(const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        std::terminate();
    }
    try
    {
        Logger::getInstance().set_log_directory_to(flags_handler.log_path);

        Utility utility(flags_handler.base_path, flags_handler.path_folder);
        utility.start();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        std::terminate();
    }
}