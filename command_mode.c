#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_mode.h"
#include "file_operations.h"

void command_mode(char *current_path) {
    char command[256];

    while (1) {
        // Clear screen
        printf("\033[H\033[J");

        // Status bar
        printf("\n[Command Mode] Current Path: %s\n", current_path);
        printf("Enter your command: ");
        fgets(command, sizeof(command), stdin);

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // Process the command
        if (strncmp(command, "copy ", 5) == 0) {
            // Parse and execute copy command
            copy_file(command + 5);
        } else if (strncmp(command, "move ", 5) == 0) {
            // Parse and execute move command
            move_file(command + 5);
        } else if (strncmp(command, "rename ", 7) == 0) {
            // Parse and execute rename command
            rename_file(command + 7);
        } else if (strncmp(command, "create_file ", 12) == 0) {
            // Parse and execute create_file command
            create_file(command + 12);
        } else if (strncmp(command, "create_dir ", 11) == 0) {
            // Parse and execute create_dir command
            create_dir(command + 11);
        } else if (strncmp(command, "delete_file ", 12) == 0) {
            // Parse and execute delete_file command
            delete_file(command + 12);
        } else if (strncmp(command, "delete_dir ", 11) == 0) {
            // Parse and execute delete_dir command
            delete_dir(command + 11);
        } else if (strncmp(command, "goto ", 5) == 0) {
            // Parse and execute goto command
            goto_dir(command + 5);
        } else if (strncmp(command, "search ", 7) == 0) {
            // Parse and execute search command
            if (search_file(current_path, command + 7)) {
                printf("File/Directory found\n");
            } else {
                printf("File/Directory not found\n");
            }
        } else if (strcmp(command, "quit") == 0) {
            exit(0);
        } else if (strcmp(command, "exit") == 0) {
            break;
        }

        printf("Press any key to continue...");
        getchar();
    }
}
