#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>
#include <vector>

void explorer(const std::string &current_path);
void list_files(const std::string &path);
void open_selected(std::string &path, bool from_enter_key = false);
void navigate(std::string &path, char ch);
void handle_arrow_keys(std::string &path, char first_char);

extern std::vector<std::string> back_stack;
extern std::vector<std::string> forward_stack;

#endif
