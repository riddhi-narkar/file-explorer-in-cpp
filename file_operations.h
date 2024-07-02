#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void list_files(const char *path);
void copy_file(const char *src, const char *dest);
void move_file(const char *src, const char *dest);
void rename_file(const char *old_name, const char *new_name);
void create_file(const char *file_name, const char *dest_path);
void create_dir(const char *dir_name, const char *dest_path);
void delete_file(const char *file_path);
void delete_dir(const char *dir_path);
void goto_dir(const char *path);
int search_file(const char *path, const char *file_name);
void open_selected(const char *path);
void navigate(const char *path, char ch);

#endif // FILE_OPERATIONS_H
