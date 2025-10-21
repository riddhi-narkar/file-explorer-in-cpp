#include <iostream>
#include <iomanip>  // For setw
#include <string>
#include <cstring>  // for strerror
#include <unistd.h> // for access, F_OK only
#include <dirent.h>
#include <sys/stat.h> // for stat only
#include <fcntl.h> // for open
#include <termios.h> // for the arrow key input
#include <pwd.h>    // For getpwuid
#include <grp.h>    // For getgrgid
#include "file_explorer.h"

// Stack to store the navigation history
std::vector<std::string> back_stack;
std::vector<std::string> forward_stack;

void list_files(const std::string &path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(path.c_str())) == NULL) {
        perror("opendir");
        return;
    }

    std::cout << std::left << std::setw(30) << "File Name"
              << std::setw(10) << "Size"
              << std::setw(20) << "Owner/Group"
              << std::setw(12) << "Permissions"
              << "Last Modified" << std::endl;

    while ((entry = readdir(dir)) != NULL) {
        std::string full_path = path + "/" + entry->d_name;

        if (stat(full_path.c_str(), &file_stat) == -1) {
            perror("stat");
            continue;
        }

        std::string file_name = entry->d_name;
        if (file_name.length() > 27) {
            file_name = file_name.substr(0, 27) + "...";
        }

        std::string owner = getpwuid(file_stat.st_uid)->pw_name;
        std::string group = getgrgid(file_stat.st_gid)->gr_name;
        std::string permissions;

        permissions += (S_ISDIR(file_stat.st_mode)) ? 'd' : '-';
        permissions += (file_stat.st_mode & S_IRUSR) ? 'r' : '-'; // USERS ://read permissions
        permissions += (file_stat.st_mode & S_IWUSR) ? 'w' : '-'; //write permissions
        permissions += (file_stat.st_mode & S_IXUSR) ? 'x' : '-'; // execute permissions
        permissions += (file_stat.st_mode & S_IRGRP) ? 'r' : '-'; //GROUPS
        permissions += (file_stat.st_mode & S_IWGRP) ? 'w' : '-';
        permissions += (file_stat.st_mode & S_IXGRP) ? 'x' : '-';
        permissions += (file_stat.st_mode & S_IROTH) ? 'r' : '-'; //OTHERS
        permissions += (file_stat.st_mode & S_IWOTH) ? 'w' : '-';
        permissions += (file_stat.st_mode & S_IXOTH) ? 'x' : '-';

        char last_modified[20];
        strftime(last_modified, sizeof(last_modified), "%Y-%m-%d %H:%M", localtime(&file_stat.st_mtime));

        std::cout << std::left << std::setw(30) << file_name
                  << std::setw(10) << file_stat.st_size
                  << std::setw(20) << (owner + "/" + group)
                  << std::setw(12) << permissions
                  << last_modified << std::endl;
    }

    closedir(dir);
}

void explorer(const std::string &current_path) {
    std::string path = current_path;

    list_files(path);

    char ch;
    while (std::cin >> ch && ch != 'q') {
        switch (ch) {
            case 'o':
                navigate(path, ch);
                break;
            case 'h':
                navigate(path, ch);
                break;
            default:
                handle_arrow_keys(path, ch); // Handle arrow key inputs
                break;
        }
        list_files(path);
    }
}

void navigate(std::string &path, char ch)
{
    std::string home_directory = getenv("HOME"); // Get the user's home directory
    std::string new_path;

    switch (ch) {
        case 'h':
            if (path != home_directory) {
                back_stack.push_back(path); // Push current path to back stack
                path = home_directory; // Navigate to home directory
            }
            break;
        case 'o': {
            std::string dir_name;
            std::cout << "Enter directory name to navigate into: ";
            std::cin >> dir_name;
            new_path = path + "/" + dir_name;
            if (access(new_path.c_str(), F_OK) == 0) {
                back_stack.push_back(path); // Push current path to back stack
                path = new_path; // Update to new directory
            } else {
                std::cout << "Directory does not exist.\n";
            }
            break;
        }
        default:
            break;
    }
}

void handle_arrow_keys(std::string &path, char first_char)
{
    if (first_char != '\033') // Check if the first character is an escape sequence
        return;

    char second_char;
    std::cin >> second_char; // Read the second character of the escape sequence

    if (second_char != '[') // Check if it is the expected second character
        return;

    char third_char;
    std::cin >> third_char; // Read the third character of the escape sequence

    switch (third_char) {
        case 'C': // Right arrow key
            if (!forward_stack.empty()) {
                back_stack.push_back(path); // Push the current path to back stack
                path = forward_stack.back(); // Navigate to the forward path
                forward_stack.pop_back(); // Remove the forward path from stack
                std::cout << "Right arrow key pressed. Going forward to " << path << "\n";
            }
            break;
        case 'D': // Left arrow key
            if (!back_stack.empty()) {
                forward_stack.push_back(path); // Push the current path to forward stack
                path = back_stack.back(); // Navigate to the back path
                back_stack.pop_back(); // Remove the back path from stack
                std::cout << "Left arrow key pressed. Going back to " << path << "\n";
            }
            break;
        default:
            break;
    }
}
