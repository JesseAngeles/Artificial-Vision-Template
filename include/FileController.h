#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <string>
#include <vector>

#include "tinyfiledialogs.h"

std::string readFile(const std::string &init_file_path = "./resources/*", const std::vector<std::string> &file_types = {});

#endif // FILE_CONTROLLER_H