#include <iostream>
#include <string>
#include <cstring>  // for strerror
#include <cstdlib>  // for access
#include <unistd.h> // for access, F_OK
#include <dirent.h>
#include <sys/stat.h> // for stat
#include <fcntl.h> // for open
#include <termios.h> // for termios related functionality
#include "normal_mode.h"
#include "file_operations.h"

void normal_mode(const std::string &current_path) {
    std::string path = current_path;

    list_files(path);

    char ch;
    while (std::cin >> ch && ch != 'q') {
        switch (ch) {
            case 'o':
                open_selected(path); // Call open_selected for manual input
                break;
            case '\n': // Enter key pressed
                open_selected(path, true); // Call open_selected for enter key press
                break;
            case 'h':
            case 'j':
            case 'k':
            case 'l':
                navigate(path, ch);
                break;
            default:
                handle_arrow_keys(path, ch); // Handle arrow key inputs
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

void open_selected(const std::string &path, bool from_enter_key) {
    std::string selected_item;

    if (!from_enter_key) {
        std::cout << "Enter the directory or file name to open: ";
        std::cin >> selected_item;
    } else {
        std::cout << "Enter the directory or file name to open (press Enter): ";
        std::cin.ignore(); // Clear any remaining newline characters from previous input
        std::getline(std::cin, selected_item); // Read entire line to handle spaces in names
    }

    std::string full_path = path + "/" + selected_item;

    struct stat stat_buf;
    if (stat(full_path.c_str(), &stat_buf) == 0) {
        if (S_ISDIR(stat_buf.st_mode)) {
            // Clear screen (not implemented here)
            std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
            std::cout << "Opening directory: " << full_path << std::endl;
            list_files(full_path); // Display contents of the directory
        } else if (S_ISREG(stat_buf.st_mode)) {
            std::cout << "Opening file in vim: " << full_path << std::endl;
            // Here you could call a function to open the file in vim
            // For now, it just prints a message
        } else {
            std::cout << "Unknown file type.\n";
        }
    } else {
        std::cerr << "Error accessing file or directory: " << strerror(errno) << std::endl;
    }
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
        // 'j' and 'k' will not change directories in this example
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

void handle_arrow_keys(std::string &path, char first_char) {
    if (first_char != '\033') // Check if the first character is an escape sequence
        return;

    char second_char;
    std::cin >> second_char; // Read the second character of the escape sequence

    if (second_char != '[') // Check if it is the expected second character
        return;

    char third_char;
    std::cin >> third_char; // Read the third character of the escape sequence

    switch (third_char) {
        case 'A': // Up arrow key
            std::cout << "Up arrow key pressed\n";
            // Implement your logic here for up arrow key
            break;
        case 'B': // Down arrow key
            std::cout << "Down arrow key pressed\n";
            // Implement your logic here for down arrow key
            break;
        case 'C': // Right arrow key
            std::cout << "Right arrow key pressed\n";
            // Implement your logic here for right arrow key
            break;
        case 'D': // Left arrow key
            std::cout << "Left arrow key pressed\n";
            // Implement your logic here for left arrow key
            break;
        default:
            break;
    }
}
