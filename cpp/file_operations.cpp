#include "file_operations.h"
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>

void copy_file(const std::string &src, const std::string &dest) {
    std::ifstream source(src, std::ios::binary);
    std::ofstream destination(dest, std::ios::binary);

    if (!source.is_open()) {
        std::cerr << "Error opening source file: " << std::strerror(errno) << "\n";
        return;
    }

    if (!destination.is_open()) {
        std::cerr << "Error opening destination file: " << std::strerror(errno) << "\n";
        source.close();
        return;
    }

    destination << source.rdbuf();

    source.close();
    destination.close();

    std::cout << "File copied successfully.\n";
}

void move_file(const std::string &src, const std::string &dest) {
    if (rename(src.c_str(), dest.c_str()) != 0) {
        std::cerr << "Error moving file: " << std::strerror(errno) << "\n";
    } else {
        std::cout << "File moved successfully.\n";
    }
}

void rename_file(const std::string &old_name, const std::string &new_name) {
    if (rename(old_name.c_str(), new_name.c_str()) != 0) {
        std::cerr << "Error renaming file: " << std::strerror(errno) << "\n";
    } else {
        std::cout << "File renamed successfully.\n";
    }
}

void create_file(const std::string &file_name, const std::string &dest_path) {
    std::ofstream new_file(dest_path + "/" + file_name);
    if (new_file.is_open()) {
        new_file.close();
        std::cout << "File created successfully.\n";
    } else {
        std::cerr << "Error creating file: " << std::strerror(errno) << "\n";
    }
}

void create_dir(const std::string &dir_name, const std::string &dest_path) {
    std::string full_path = dest_path + "/" + dir_name;

    // Check if directory already exists
    struct stat st;
    if (stat(full_path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        std::cerr << "Directory already exists.\n";
        return;
    }

    // Create directory
    if (mkdir(full_path.c_str(), 0777) == -1) {
        std::cerr << "Error creating directory: " << std::strerror(errno) << "\n";
    } else {
        std::cout << "Directory created successfully.\n";
    }
}
