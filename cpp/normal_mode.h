#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

#include <string>
using namespace std;

void normal_mode(const string &current_path);
void list_files(const string &path);
void open_selected(const string &path);
void navigate(string &path, char ch);

#endif
