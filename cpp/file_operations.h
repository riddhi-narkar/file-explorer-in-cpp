#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>

void copy_file(const std::string &src, const std::string &dest);
void move_file(const std::string &src, const std::string &dest);
void rename_file(const std::string &old_name, const std::string &new_name);
void create_file(const std::string &file_name, const std::string &dest_path);
void create_dir(const std::string &dir_name, const std::string &dest_path);

#endif
