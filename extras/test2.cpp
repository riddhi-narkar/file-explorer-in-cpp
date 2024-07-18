#include <iostream>
#include <string>
#include <cstring>  // for strerror
#include <unistd.h> // for access, F_OK only
#include <dirent.h>
#include <sys/stat.h> // for stat only
#include <fcntl.h> // for open
#include <pwd.h> // for getpwuid
#include <grp.h> // for getgrgid
#include <time.h> // for time formatting
#include <termios.h> // for the arrow key input
#include "normal_mode.h"
#include "file_operations.h"
using namespace std;

void normal_mode(const string &current_path) {
    string path = current_path;

    list_files(path);

    char ch;
    while (cin >> ch && ch != 'q') {
        switch (ch) {
            case 'o':
                open_selected(path); // Call open_selected for manual input
                break;
            case '\n': // Enter key pressed
                open_selected(path, true); // Call open_selected for enter key press
                break;
            case 'h':
            case 'j':
            case 'k':
            case 'l':
                navigate(path, ch);
                break;
            default:
                handle_arrow_keys(path, ch); // Handle arrow key inputs
                break;
        }
        list_files(path);
    }
}

void list_files(const string &path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(path.c_str())) == NULL) {
        perror("opendir");
        return;
    }

    cout << "Listing files in " << path << ":\n";
    while ((entry = readdir(dir)) != NULL) {
        string full_path = path + "/" + entry->d_name;

        if (stat(full_path.c_str(), &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // File name
        cout << entry->d_name;

        // File size
        cout << "\t" << file_stat.st_size;

        // Ownership (user and group)
        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        if (pw != NULL && gr != NULL) {
            cout << "\t" << pw->pw_name << "/" << gr->gr_name;
        } else {
            cout << "\t" << file_stat.st_uid << "/" << file_stat.st_gid;
        }

        // Permissions
        cout << "\t";
        cout << ((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        cout << ((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        cout << ((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        cout << ((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        cout << ((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        cout << ((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        cout << ((file_stat.st_mode & S_IROTH) ? "r" : "-");
        cout << ((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        cout << ((file_stat.st_mode & S_IXOTH) ? "x" : "-");

        // Last modified
        char time_buf[80];
        struct tm *time_info = localtime(&file_stat.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", time_info);
        cout << "\t" << time_buf;

        cout << endl;
    }

    closedir(dir);
}

void open_selected(string &path, bool from_enter_key) {
    string selected_item;

    if (!from_enter_key) {
        cout << "Enter the directory or file name to open: ";
        cin >> selected_item;
    } else {
        cout << "Enter the directory or file name to open (press Enter): ";
        cin.ignore(); // Clear any remaining newline characters from previous input
        getline(cin, selected_item); // Read entire line to handle spaces in names
    }

    string full_path = path +
