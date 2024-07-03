#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH 1024
#define MAX_FILES 1000

void list_files(const char *path);
void normal_mode();
void command_mode();
void copy_file(const char *src, const char *dest);
void move_file(const char *src, const char *dest);
void rename_file(const char *old_name, const char *new_name);
void create_file(const char *file_name, const char *dest_path);
void create_dir(const char *dir_name, const char *dest_path);
void delete_file(const char *file_path);
void delete_dir(const char *dir_path);
void goto_dir(const char *path);
int search_file(const char *path, const char *file_name);

int main() {
    // Start in normal mode
    normal_mode();
    return 0;
}

void normal_mode() {
    char current_path[MAX_PATH];
    getcwd(current_path, sizeof(current_path));

    while (1) {
        // Clear screen
        printf("\033[H\033[J");

        // List files in the current directory
        list_files(current_path);

        // Status bar
        printf("\n[Normal Mode] Current Path: %s\n", current_path);
        printf("Press ':' to enter Command Mode, 'q' to quit.\n");

        // Capture user input
        char ch = getchar();
        if (ch == ':') {
            command_mode();
        } else if (ch == 'q') {
            break;
        }
    }
}

void command_mode() {
    char command[256];

    // Clear screen
    printf("\033[H\033[J");

    // Status bar
    printf("\n[Command Mode]\n");
    printf("Enter your command: ");
    fgets(command, sizeof(command), stdin);

    // Process the command
    if (strncmp(command, "copy ", 5) == 0) {
        // Parse and execute copy command
    } else if (strncmp(command, "move ", 5) == 0) {
        // Parse and execute move command
    } else if (strncmp(command, "rename ", 7) == 0) {
        // Parse and execute rename command
    } else if (strncmp(command, "create_file ", 12) == 0) {
        // Parse and execute create_file command
    } else if (strncmp(command, "create_dir ", 11) == 0) {
        // Parse and execute create_dir command
    } else if (strncmp(command, "delete_file ", 12) == 0) {
        // Parse and execute delete_file command
    } else if (strncmp(command, "delete_dir ", 11) == 0) {
        // Parse and execute delete_dir command
    } else if (strncmp(command, "goto ", 5) == 0) {
        // Parse and execute goto command
    } else if (strncmp(command, "search ", 7) == 0) {
        // Parse and execute search command
    } else if (strncmp(command, "quit", 4) == 0) {
        exit(0);
    }
}

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

// Implement the remaining functions similarly
