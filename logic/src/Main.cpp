#include <iostream>
#include <source_location>

#include "FlagsHandler.hpp"
#include "Output.hpp"
#include "Scanner.hpp"

int main(int argc, char* argv[])
{
    FlagsHandler flags_handler;

    try
    {
        flags_handler.parse(std::vector<std::string>(argv + 1, argv + argc));
    }
    catch(const std::exception& exception)
    {
        auto location = std::source_location::current();
        std::clog << "file: "
                    << location.file_name() << '('
                    << location.line() << ':'
                    << location.column() << ") `"
                    << location.function_name() << "`: " 
                    << exception.what() << '\n';

        return EXIT_FAILURE;
    }

    try
    {
        Logger::get_instance().set_log_directory_to(flags_handler.log_path);

        Scanner scanner(flags_handler.base_path, flags_handler.path_folder);
        scanner.start();
    }
    catch (const std::exception& exception)
    {
        auto location = std::source_location::current();
        std::clog << "file: "
                    << location.file_name() << '('
                    << location.line() << ':'
                    << location.column() << ") `"
                    << location.function_name() << "`: "
                    << exception.what() << '\n';

        return EXIT_FAILURE;
    }
}