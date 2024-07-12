#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include "command_mode.h"
#include "file_operations.h" // Assuming you have file operations defined here

void execute_command(const std::string &command, std::string &current_path) {
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
        if (tokens.size() < 4) {
            std::cout << "Usage: $ copy <source_file(s)> <destination_directory>\n";
            return;
        }
        std::vector<std::string> sources(tokens.begin() + 1, tokens.end() - 1);
        std::string destination = tokens.back();
        copy_file(source, destination);
    } else if (cmd == "move") {
        if (tokens.size() < 4) {
            std::cout << "Usage: $ move <source_file(s)> <destination_directory>\n";
            return;
        }
        std::vector<std::string> sources(tokens.begin() + 1, tokens.end() - 1);
        std::string destination = tokens.back();
        move_file(source, destination);
    } else if (cmd == "rename") {
        if (tokens.size() != 3) {
            std::cout << "Usage: $ rename <old_filename> <new_filename>\n";
            return;
        }
        std::string old_name = tokens[1];
        std::string new_name = tokens[2];
        rename_file(old_name, new_name);
    } else if (cmd == "create_file") {
        if (tokens.size() != 3) {
            std::cout << "Usage: $ create_file <file_name> <destination_path>\n";
            return;
        }
        std::string file_name = tokens[1];
        std::string destination = tokens[2];
        create_file(file_name, destination);
    } else if (cmd == "create_dir") {
        if (tokens.size() != 3) {
            std::cout << "Usage: $ create_dir <dir_name> <destination_path>\n";
            return;
        }
        std::string dir_name = tokens[1];
        std::string destination = tokens[2];
        create_directory(dir_name, destination);
    } else if (cmd == "delete_file") {
        if (tokens.size() != 2) {
            std::cout << "Usage: $ delete_file <file_path>\n";
            return;
        }
        std::string file_path = tokens[1];
        delete_file(file_path);
    } else if (cmd == "delete_dir") {
        if (tokens.size() != 2) {
            std::cout << "Usage: $ delete_dir <dir_path>\n";
            return;
        }
        std::string dir_path = tokens[1];
        delete_directory(dir_path);
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




// #include <iostream>
// #include <string>
// #include "command_mode.h"
// #include "file_operations.h"

// void command_mode(const std::string &current_path) {
//     std::string command;
//     std::cout << "Enter command: ";
//     std::cin >> command;

//     if (command.rfind("copy ", 0) == 0) {
//         std::string args = command.substr(5);
//         size_t space_pos = args.find(' ');
//         if (space_pos != std::string::npos) {
//             std::string src = args.substr(0, space_pos);
//             std::string dest = args.substr(space_pos + 1);
//             copy_file(src, dest);
//         }
//     } else if (command.rfind("move ", 0) == 0) {
//         std::string args = command.substr(5);
//         size_t space_pos = args.find(' ');
//         if (space_pos != std::string::npos) {
//             std::string src = args.substr(0, space_pos);
//             std::string dest = args.substr(space_pos + 1);
//             move_file(src, dest);
//         }
//     } else if (command.rfind("rename ", 0) == 0) {
//         std::string args = command.substr(7);
//         size_t space_pos = args.find(' ');
//         if (space_pos != std::string::npos) {
//             std::string old_name = args.substr(0, space_pos);
//             std::string new_name = args.substr(space_pos + 1);
//             rename_file(old_name, new_name);
//         }
//     } else if (command.rfind("create_file ", 0) == 0) {
//         std::string args = command.substr(12);
//         size_t space_pos = args.find(' ');
//         if (space_pos != std::string::npos) {
//             std::string file_name = args.substr(0, space_pos);
//             std::string dest_path = args.substr(space_pos + 1);
//             create_file(file_name, dest_path);
//         }
//     } else if (command.rfind("create_dir ", 0) == 0) {
//         std::string args = command.substr(11);
//         size_t space_pos = args.find(' ');
//         if (space_pos != std::string::npos) {
//             std::string dir_name = args.substr(0, space_pos);
//             std::string dest_path = args.substr(space_pos + 1);
//             create_dir(dir_name, dest_path);
//         }
//     }
// }

// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include "command_mode.h"
// #include "file_operations.h"

// std::vector<std::string> parse_command(const std::string &command) {
//     std::istringstream iss(command);
//     return std::vector<std::string>{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
// }

// void command_mode(const std::string &current_path) {
//     std::string command;
//     std::cout << "Enter command: ";
//     std::getline(std::cin, command);

//     std::vector<std::string> tokens = parse_command(command);
//     if (tokens.empty()) return;

//     const std::string &cmd = tokens[0];
//     if (cmd == "copy" && tokens.size() >= 3) {
//         std::vector<std::string> src_files(tokens.begin() + 1, tokens.end() - 1);
//         const std::string &dest_dir = tokens.back();
//         for (const auto &src : src_files) {
//             copy_file(src, dest_dir);
//         }
//     } else if (cmd == "move" && tokens.size() >= 3) {
//         std::vector<std::string> src_files(tokens.begin() + 1, tokens.end() - 1);
//         const std::string &dest_dir = tokens.back();
//         for (const auto &src : src_files) {
//             move_file(src, dest_dir);
//         }
//     } else if (cmd == "rename" && tokens.size() == 3) {
//         rename_file(tokens[1], tokens[2]);
//     } else if (cmd == "create_file" && tokens.size() == 3) {
//         create_file(tokens[1], tokens[2]);
//     } else if (cmd == "create_dir" && tokens.size() == 3) {
//         create_dir(tokens[1], tokens[2]);
//     } else {
//         std::cout << "Invalid command or incorrect number of arguments.\n";
//     }
// }
