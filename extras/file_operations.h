#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>

bool copy_file(const std::string &source, const std::string &destination);
bool move_file(const std::string &source, const std::string &destination);
bool rename_file(const std::string &old_name, const std::string &new_name);
// bool create_file(const std::string &file_name, const std::string &destination_path);
// bool create_directory(const std::string &dir_name, const std::string &destination_path);
// bool delete_file(const std::string &file_path);
// bool delete_directory(const std::string &dir_path);

#endif // FILE_OPERATIONS_H
