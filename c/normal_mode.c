#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include "normal_mode.h"
#include "file_operations.h"

#define PATH_MAX 4096

void normal_mode(const char *current_path) {
    char path[PATH_MAX];
    strncpy(path, current_path, PATH_MAX - 1);
    path[PATH_MAX - 1] = '\0';

    list_files(path);

    int ch;
    while ((ch = getchar()) != 'q') {
        switch (ch) {
            case 'o':
                open_selected(path);
                break;
            case 'h':
                navigate(path, 'h');
                break;
            case 'j':
                navigate(path, 'j');
                break;
            case 'k':
                navigate(path, 'k');
                break;
            case 'l':
                navigate(path, 'l');
                break;
            default:
                break;
        }
        list_files(path);
    }
}

void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    printf("Listing files in %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void open_selected(const char *path) {
    char selected_file[256];
    printf("Enter the file name to open: ");
    scanf("%s", selected_file);

    char full_path[PATH_MAX];
    snprintf(full_path, PATH_MAX, "%s/%s", path, selected_file);

    if (access(full_path, F_OK) == -1) {
        printf("File does not exist.\n");
        return;
    }

    printf("Opening file: %s\n", full_path);
    // Here you could add the logic to actually open the file
    // For now, it just prints a message
}

void navigate(char *path, char ch) {
    char new_path[PATH_MAX];

    switch (ch) {
        case 'h':
            if (strcmp(path, "/") != 0) { // Check if not already in root directory
                char *last_slash = strrchr(path, '/');
                if (last_slash != NULL) {
                    *last_slash = '\0'; // Move up one directory
                }
                if (path[0] == '\0') {
                    strncpy(path, "/", PATH_MAX - 1); // Special case for root directory
                }
            }
            break;
        case 'l':
            printf("Enter directory name to navigate into: ");
            char dir_name[256];
            scanf("%s", dir_name);
            snprintf(new_path, PATH_MAX, "%s/%s", path, dir_name);
            if (access(new_path, F_OK) == 0) {
                strncpy(path, new_path, PATH_MAX - 1);
            } else {
                printf("Directory does not exist.\n");
            }
            break;
        // For simplicity, 'j' and 'k' will not change directories in this example
        case 'j':
            printf("Scroll down (not implemented)\n");
            break;
        case 'k':
            printf("Scroll up (not implemented)\n");
            break;
        default:
            break;
    }
}
