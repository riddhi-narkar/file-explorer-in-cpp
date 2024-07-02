#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "normal_mode.h"
#include "file_operations.h"
#include "command_mode.h"

#define MAX_PATH 1024

void normal_mode()
{
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
            command_mode(current_path);
        } else if (ch == 'q') {
            break;
        } else if (ch == '\n') {
            // Handle enter key for opening files/directories
            open_selected(current_path);
        } else if (ch == 27) {
            // Handle arrow keys for navigation
            navigate(current_path, ch);
        }
    }
}
