#include <iostream>
#include <string>
#include "file_explorer.h"
using namespace std;

int main() {
    string current_path = "/"; // Starting path is the root directory
    bool running = true;

    while (running) {
        explorer(current_path);

        // After normal_mode completes, check for 'q' to quit
        std::cout << "Press 'q' to quit or any other key to refresh: ";
        char input;
        std::cin >> input;

        if (input == 'q') {
            running = false; // Quit the application
        }
    }

    std::cout << "Exiting File Explorer Application.\n";
    return 0;
}
