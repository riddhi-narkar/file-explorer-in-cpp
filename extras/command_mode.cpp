// #include <iostream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <pwd.h>
// #include <grp.h>
// #include "command_mode.h"
// #include "file_operations.h"

// void execute_command(const std::string &command, const std::string &current_path) {
//     std::istringstream iss(command);
//     std::vector<std::string> tokens;
//     std::string token;

//     while (iss >> token) {
//         tokens.push_back(token);
//     }

//     if (tokens.empty()) {
//         std::cout << "Invalid command format.\n";
//         return;
//     }

//     std::string cmd = tokens[0];
//     if (cmd == "copy") {
//         if (tokens.size() < 4) {
//             std::cout << "Usage: $ copy <source_file(s)> <destination_directory>\n";
//             return;
//         }
//         std::vector<std::string> sources(tokens.begin() + 1, tokens.end() - 1);
//         std::string destination = tokens.back();
//         for (const auto &source : sources) {
//             if (!copy_file(source, destination)) {
//                 std::cerr << "Error copying " << source << " to " << destination << std::endl;
//             }
//         }
//     } else if (cmd == "move") {
//         if (tokens.size() < 4) {
//             std::cout << "Usage: $ move <source_file(s)> <destination_directory>\n";
//             return;
//         }
//         std::vector<std::string> sources(tokens.begin() + 1, tokens.end() - 1);
//         std::string destination = tokens.back();
//         for (const auto &source : sources) {
//             if (!move_file(source, destination)) {
//                 std::cerr << "Error moving " << source << " to " << destination << std::endl;
//             }
//         }
//     } else if (cmd == "rename") {
//         if (tokens.size() != 3) {
//             std::cout << "Usage: $ rename <old_filename> <new_filename>\n";
//             return;
//         }
//         std::string old_name = tokens[1];
//         std::string new_name = tokens[2];
//         if (!rename_file(old_name, new_name)) {
//             std::cerr << "Error renaming " << old_name << " to " << new_name << std::endl;
//         }
//     }
//      else {
//         std::cout << "Unknown command.\n";
//     }
// }

// void command_mode(const std::string &current_path) {
//     std::string command;
//     bool running = true;

//     while (running) {
//         std::cout << "Command Mode: ";
//         std::getline(std::cin, command);

//         if (command.empty()) {
//             continue;
//         } else if (command == "exit") {
//             running = false;
//         } else {
//             execute_command(command, current_path);
//         }
//     }

//     std::cout << "Exiting Command Mode.\n";
// }

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "command_mode.h"
#include "file_operations.h"

void execute_command(const std::string &command, const std::string &current_path) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        std::cout << "Invalid command format.\n";
        return;
    }

    std::string cmd = tokens[0];
    if (cmd == "copy") {
        if (tokens.size() != 3) {
            std::cout << "Usage: copy <file/directory_name> <destination_path>\n";
            return;
        }
        std::string source = tokens[1];
        std::string destination = tokens[2];
        if (!copy_file(source, destination)) {
            std::cerr << "Error copying " << source << " to " << destination << std::endl;
        }
    } else {
        std::cout << "Unknown command.\n";
    }
}

void command_mode(const std::string &current_path) {
    std::string command;
    bool running = true;

    while (running) {
        std::cout << "Command Mode: ";
        std::getline(std::cin, command);

        if (command.empty()) {
            continue;
        } else if (command == "exit") {
            running = false;
        } else {
            execute_command(command, current_path);
        }
    }

    std::cout << "Exiting Command Mode.\n";
}
