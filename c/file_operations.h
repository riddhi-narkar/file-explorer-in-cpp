#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void copy_file(const char *src, const char *dest);
void move_file(const char *src, const char *dest);
void rename_file(const char *old_name, const char *new_name);
void create_file(const char *file_name, const char *dest_path);
void create_dir(const char *dir_name, const char *dest_path);

#endif // FILE_OPERATIONS_H
