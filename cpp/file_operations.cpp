#include "file_operations.h"
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <string>

// Utility function to copy files
bool copy_file_content(const std::string &src, const std::string &dest) {
    std::ifstream src_stream(src, std::ios::binary);
    std::ofstream dest_stream(dest, std::ios::binary);
    dest_stream << src_stream.rdbuf();
    return src_stream && dest_stream;
}

void copy_file(const std::string &src, const std::string &dest) {
    struct stat info;
    if (stat(src.c_str(), &info) != 0) {
        std::cerr << "Error: Cannot access " << src << ": " << std::strerror(errno) << "\n";
        return;
    }

    if (S_ISDIR(info.st_mode)) {
        copy_directory(src, dest);
    } else {
        std::string dest_file = dest + "/" + src.substr(src.find_last_of("/\\") + 1);
        if (copy_file_content(src, dest_file)) {
            std::cout << "File copied successfully.\n";
        } else {
            std::cerr << "Error copying file.\n";
        }
    }
}

void copy_directory(const std::string &src, const std::string &dest) {
    DIR *dir = opendir(src.c_str());
    if (!dir) {
        std::cerr << "Error: Cannot open directory " << src << ": " << std::strerror(errno) << "\n";
        return;
    }

    std::string dest_dir = dest + "/" + src.substr(src.find_last_of("/\\") + 1);
    mkdir(dest_dir.c_str(), 0777);

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string entry_name = entry->d_name;
        if (entry_name == "." || entry_name == "..") continue;

        std::string src_path = src + "/" + entry_name;
        std::string dest_path = dest_dir;

        struct stat entry_info;
        if (stat(src_path.c_str(), &entry_info) != 0) {
            std::cerr << "Error: Cannot access " << src_path << ": " << std::strerror(errno) << "\n";
            continue;
        }

        if (S_ISDIR(entry_info.st_mode)) {
            copy_directory(src_path, dest_path);
        } else {
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
    std::cout << "Directory copied successfully.\n";
}

void move_file(const std::string &src, const std::string &dest) {
    std::string dest_file = dest + "/" + src.substr(src.find_last_of("/\\") + 1);
    if (rename(src.c_str(), dest_file.c_str()) == 0) {
        std::cout << "File moved successfully.\n";
    } else {
        std::cerr << "Error moving file: " << std::strerror(errno) << "\n";
    }
}

void move_directory(const std::string &src, const std::string &dest) {
    std::string dest_dir = dest + "/" + src.substr(src.find_last_of("/\\") + 1);
    if (rename(src.c_str(), dest_dir.c_str()) == 0) {
        std::cout << "Directory moved successfully.\n";
    } else {
        std::cerr << "Error moving directory: " << std::strerror(errno) << "\n";
    }
}

void rename_file(const std::string &old_name, const std::string &new_name) {
    if (rename(old_name.c_str(), new_name.c_str()) == 0) {
        std::cout << "File renamed successfully.\n";
    } else {
        std::cerr << "Error renaming file: " << std::strerror(errno) << "\n";
    }
}

void create_file(const std::string &file_name, const std::string &dest_path) {
    std::string full_path = dest_path + "/" + file_name;
    std::ofstream new_file(full_path);
    if (new_file.is_open()) {
        new_file.close();
        std::cout << "File created successfully.\n";
    } else {
        std::cerr << "Error creating file: " << std::strerror(errno) << "\n";
    }
}

void create_dir(const std::string &dir_name, const std::string &dest_path) {
    std::string full_path = dest_path + "/" + dir_name;
    if (mkdir(full_path.c_str(), 0777) == 0) {
        std::cout << "Directory created successfully.\n";
    } else {
        std::cerr << "Error creating directory: " << std::strerror(errno) << "\n";
    }
}
