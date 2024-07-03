#include <iostream>
#include <string>
#include "command_mode.h"
#include "file_operations.h"

void command_mode(const std::string &current_path) {
    std::string command;
    std::cout << "Enter command: ";
    std::cin >> command;

    if (command.rfind("copy ", 0) == 0) {
        std::string args = command.substr(5);
        size_t space_pos = args.find(' ');
        if (space_pos != std::string::npos) {
            std::string src = args.substr(0, space_pos);
            std::string dest = args.substr(space_pos + 1);
            copy_file(src, dest);
        }
    } else if (command.rfind("move ", 0) == 0) {
        std::string args = command.substr(5);
        size_t space_pos = args.find(' ');
        if (space_pos != std::string::npos) {
            std::string src = args.substr(0, space_pos);
            std::string dest = args.substr(space_pos + 1);
            move_file(src, dest);
        }
    } else if (command.rfind("rename ", 0) == 0) {
        std::string args = command.substr(7);
        size_t space_pos = args.find(' ');
        if (space_pos != std::string::npos) {
            std::string old_name = args.substr(0, space_pos);
            std::string new_name = args.substr(space_pos + 1);
            rename_file(old_name, new_name);
        }
    } else if (command.rfind("create_file ", 0) == 0) {
        std::string args = command.substr(12);
        size_t space_pos = args.find(' ');
        if (space_pos != std::string::npos) {
            std::string file_name = args.substr(0, space_pos);
            std::string dest_path = args.substr(space_pos + 1);
            create_file(file_name, dest_path);
        }
    } else if (command.rfind("create_dir ", 0) == 0) {
        std::string args = command.substr(11);
        size_t space_pos = args.find(' ');
        if (space_pos != std::string::npos) {
            std::string dir_name = args.substr(0, space_pos);
            std::string dest_path = args.substr(space_pos + 1);
            create_dir(dir_name, dest_path);
        }
    }
}
