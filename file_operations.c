#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "file_operations.h"

#define MAX_PATH 1024

void list_files(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    char full_path[MAX_PATH];
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Display file information
        printf("%-20s %10ld %10s %10s %s\n", entry->d_name, file_stat.st_size,
               getpwuid(file_stat.st_uid)->pw_name, getgrgid(file_stat.st_gid)->gr_name,
               ctime(&file_stat.st_mtime));
    }

    closedir(dir);
}

void copy_file(const char *src, const char *dest) {
    FILE *source, *destination;
    char buffer[BUFSIZ];
    size_t bytes;

    source = fopen(src, "rb");
    if (source == NULL) {
        perror("fopen src");
        return;
    }

    destination = fopen(dest, "wb");
    if (destination == NULL) {
        perror("fopen dest");
        fclose(source);
        return;
    }

    while ((bytes = fread(buffer, 1, BUFSIZ, source)) > 0) {
        fwrite(buffer, 1, bytes, destination);
    }

    fclose(source);
    fclose(destination);
}

void move_file(const char *src, const char *dest) {
    if (rename(src, dest) != 0) {
        perror("rename");
    }
}

void rename_file(const char *old_name, const char *new_name) {
    if (rename(old_name, new_name) != 0) {
        perror("rename");
    }
}

void create_file(const char *file_name, const char *dest_path) {
    char full_path[MAX_PATH];
    snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, file_name);

    FILE *file = fopen(full_path, "w");
    if (file == NULL) {
        perror("fopen");
        return;
    }
    fclose(file);
}

void create_dir(const char *dir_name, const char *dest_path) {
    char full_path[MAX_PATH];
    snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, dir_name);

    if (mkdir(full_path, 0755) != 0) {
        perror("mkdir");
    }
}

void delete_file(const char *file_path) {
    if (remove(file_path) != 0) {
        perror("remove");
    }
}

void delete_dir(const char *dir_path) {
    if (rmdir(dir_path) != 0) {
        perror("rmdir");
    }
}

void goto_dir(const char *path) {
    if (chdir(path) != 0) {
        perror("chdir");
    }
}

int search_file(const char *path, const char *file_name) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, file_name) == 0) {
            closedir(dir);
            return 1;
        }

        if (entry->d_type == DT_DIR) {
            char new_path[MAX_PATH];
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                if (search_file(new_path, file_name)) {
                    closedir(dir);
                    return 1;
                }
            }
        }
    }

    closedir(dir);
    return 0;
}

void open_selected(const char *path) {
    // Implementation for opening selected file or directory
}

void navigate(const char *path, char ch) {
    // Implementation for navigating through files and directories
}
