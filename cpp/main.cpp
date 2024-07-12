#include <iostream>
#include <string>
#include "normal_mode.h"
#include "command_mode.h"

int main() {
    std::string current_path = "/"; // Starting path is the root directory

    char mode = 'n'; // 'n' for normal mode, 'c' for command mode
    bool running = true;

    while (running) {
        if (mode == 'n') {
            normal_mode(current_path);

            // After normal_mode completes, check for colon (:) to switch to command mode
            std::cout << "Press ':' to enter command mode or 'q' to quit: ";
            char input;
            std::cin >> input;

            if (input == ':') {
                mode = 'c'; // Switch to command mode
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            } else if (input == 'q') {
                running = false; // Quit the application
            }
        } else if (mode == 'c') {
            command_mode(current_path);

            // After command mode, switch back to normal mode
            mode = 'n';
        }
    }

    std::cout << "Exiting File Explorer Application.\n";
    return 0;
}
