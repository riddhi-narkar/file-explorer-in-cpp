#include <iostream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include "normal_mode.h"
#include "file_operations.h"

void normal_mode(const std::string &current_path) {
    std::string path = current_path;

    list_files(path);

    char ch;
    while (std::cin >> ch && ch != 'q') {
        switch (ch) {
            case 'o':
                open_selected(path);
                break;
            case 'h':
                navigate(path, 'h');
                break;
            case 'j':
                navigate(path, 'j');
                break;
            case 'k':
                navigate(path, 'k');
                break;
            case 'l':
                navigate(path, 'l');
                break;
            default:
                break;
        }
        list_files(path);
    }
}

void list_files(const std::string &path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path.c_str())) == NULL) {
        perror("opendir");
        return;
    }

    std::cout << "Listing files in " << path << ":\n";
    while ((entry = readdir(dir)) != NULL) {
        std::cout << entry->d_name << std::endl;
    }

    closedir(dir);
}

void open_selected(const std::string &path) {
    std::string selected_file;
    std::cout << "Enter the file name to open: ";
    std::cin >> selected_file;

    std::string full_path = path + "/" + selected_file;

    if (access(full_path.c_str(), F_OK) == -1) {
        std::cout << "File does not exist.\n";
        return;
    }

    std::cout << "Opening file: " << full_path << std::endl;
    // Here you could add the logic to actually open the file
    // For now, it just prints a message
}

void navigate(std::string &path, char ch) {
    std::string new_path;

    switch (ch) {
        case 'h':
            if (path != "/") { // Check if not already in root directory
                size_t last_slash = path.find_last_of('/');
                if (last_slash != std::string::npos) {
                    path = path.substr(0, last_slash); // Move up one directory
                }
                if (path.empty()) {
                    path = "/"; // Special case for root directory
                }
            }
            break;
        case 'l': {
            std::string dir_name;
            std::cout << "Enter directory name to navigate into: ";
            std::cin >> dir_name;
            new_path = path + "/" + dir_name;
            if (access(new_path.c_str(), F_OK) == 0) {
                path = new_path;
            } else {
                std::cout << "Directory does not exist.\n";
            }
            break;
        }
        // For simplicity, 'j' and 'k' will not change directories in this example
        case 'j':
            std::cout << "Scroll down (not implemented)\n";
            break;
        case 'k':
            std::cout << "Scroll up (not implemented)\n";
            break;
        default:
            break;
    }
}
