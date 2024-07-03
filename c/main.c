#include <stdio.h>
#include "normal_mode.h"
#include "command_mode.h"

int main() {
    const char *initial_path = "."; // Use current directory as the initial path

    printf("Starting in normal mode...\n");
    normal_mode(initial_path);

    printf("Switching to command mode...\n");
    command_mode(initial_path);

    return 0;
}
