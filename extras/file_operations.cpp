// #include "file_operations.h"
// #include <iostream>
// #include <fstream>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <dirent.h>
// #include <cstring>
// #include <cerrno>

// bool copy_file(const std::string &source, const std::string &destination) {
//     std::ifstream src(source, std::ios::binary);
//     std::ofstream dst(destination, std::ios::binary);

//     if (!src.is_open()) {
//         std::cerr << "Error: Failed to open source file: " << source << std::endl;
//         return false;
//     }

//     if (!dst.is_open()) {
//         std::cerr << "Error: Failed to open destination file: " << destination << std::endl;
//         src.close();
//         return false;
//     }

//     dst << src.rdbuf();

//     src.close();
//     dst.close();

//     return true;
// }

// bool move_file(const std::string &source, const std::string &destination) {
//     if (rename(source.c_str(), destination.c_str()) != 0) {
//         std::cerr << "Error: Failed to move file. " << strerror(errno) << std::endl;
//         return false;
//     }
//     return true;
// }

// bool rename_file(const std::string &old_name, const std::string &new_name) {
//     if (rename(old_name.c_str(), new_name.c_str()) != 0) {
//         std::cerr << "Error: Failed to rename file. " << strerror(errno) << std::endl;
//         return false;
//     }
//     return true;
// }

#include "file_operations.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <cerrno>

bool copy_file(const std::string &source, const std::string &destination) {
    struct stat source_stat;
    if (stat(source.c_str(), &source_stat) != 0) {
        std::cerr << "Error: Cannot access source file " << source << ": " << strerror(errno) << std::endl;
        return false;
    }

    if (S_ISDIR(source_stat.st_mode)) {
        std::cerr << "Error: " << source << " is a directory. Directory copy is not implemented yet.\n";
        return false;
    }

    std::ifstream src(source, std::ios::binary);
    if (!src.is_open()) {
        std::cerr << "Error: Failed to open source file: " << source << std::endl;
        return false;
    }

    std::ofstream dst(destination, std::ios::binary);
    if (!dst.is_open()) {
        std::cerr << "Error: Failed to open destination file: " << destination << std::endl;
        src.close();
        return false;
    }

    dst << src.rdbuf();

    if (!dst) {
        std::cerr << "Error: Failed to write to destination file: " << destination << std::endl;
        src.close();
        dst.close();
        return false;
    }

    src.close();
    dst.close();

    return true;
}
