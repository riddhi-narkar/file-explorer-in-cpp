#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_mode.h"
#include "file_operations.h"

void command_mode(const char *current_path) {
    (void)current_path; // Mark current_path as unused
    char command[256];

    while (1) {
        printf(": ");
        fgets(command, 256, stdin);

        // Remove trailing newline character
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "copy ", 5) == 0) {
            char src[128], dest[128];
            sscanf(command + 5, "%s %s", src, dest);
            copy_file(src, dest);
        } else if (strncmp(command, "move ", 5) == 0) {
            char src[128], dest[128];
            sscanf(command + 5, "%s %s", src, dest);
            move_file(src, dest);
        } else if (strncmp(command, "rename ", 7) == 0) {
            char old_name[128], new_name[128];
            sscanf(command + 7, "%s %s", old_name, new_name);
            rename_file(old_name, new_name);
        } else if (strncmp(command, "create_file ", 12) == 0) {
            char file_name[128], dest_path[128];
            sscanf(command + 12, "%s %s", file_name, dest_path);
            create_file(file_name, dest_path);
        } else if (strncmp(command, "create_dir ", 11) == 0) {
            char dir_name[128], dest_path[128];
            sscanf(command + 11, "%s %s", dir_name, dest_path);
            create_dir(dir_name, dest_path);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }
    }
}
