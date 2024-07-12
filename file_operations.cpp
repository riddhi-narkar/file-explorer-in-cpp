#include "file_operations.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <cerrno>

bool copy_file(const std::string &source, const std::string &destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(destination, std::ios::binary);

    if (!src.is_open()) {
        std::cerr << "Error: Failed to open source file: " << source << std::endl;
        return false;
    }

    if (!dst.is_open()) {
        std::cerr << "Error: Failed to open destination file: " << destination << std::endl;
        src.close();
        return false;
    }

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool move_file(const std::string &source, const std::string &destination) {
    if (rename(source.c_str(), destination.c_str()) != 0) {
        std::cerr << "Error: Failed to move file. " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool rename_file(const std::string &old_name, const std::string &new_name) {
    if (rename(old_name.c_str(), new_name.c_str()) != 0) {
        std::cerr << "Error: Failed to rename file. " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool create_file(const std::string &file_name, const std::string &destination_path) {
    std::string full_path = destination_path + "/" + file_name;

    std::ofstream file(full_path);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to create file: " << full_path << std::endl;
        return false;
    }
    file.close();
    return true;
}

bool create_directory(const std::string &dir_name, const std::string &destination_path) {
    std::string full_path = destination_path + "/" + dir_name;

    if (mkdir(full_path.c_str(), 0777) != 0) {
        std::cerr << "Error: Failed to create directory: " << full_path << std::endl;
        return false;
    }
    return true;
}

bool delete_file(const std::string &file_path) {
    if (std::remove(file_path.c_str()) != 0) {
        std::cerr << "Error: Failed to delete file: " << file_path << std::endl;
        return false;
    }
    return true;
}

bool delete_directory(const std::string &dir_path) {
    DIR *dir = opendir(dir_path.c_str());
    if (dir == nullptr) {
        std::cerr << "Error: Failed to open directory: " << dir_path << std::endl;
        return false;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string sub_dir = entry->d_name;
            if (sub_dir != "." && sub_dir != "..") {
                std::string full_path = dir_path + "/" + sub_dir;
                delete_directory(full_path); // Recursive call
            }
        } else {
            std::string file_name = entry->d_name;
            std::string full_path = dir_path + "/" + file_name;
            if (std::remove(full_path.c_str()) != 0) {
                std::cerr << "Error: Failed to delete file: " << full_path << std::endl;
                return false;
            }
        }
    }

    closedir(dir);

    if (rmdir(dir_path.c_str()) != 0) {
        std::cerr << "Error: Failed to delete directory: " << dir_path << std::endl;
        return false;
    }

    return true;
}
