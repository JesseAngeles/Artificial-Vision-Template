#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <string>
#include <vector>
#include "tinyfiledialogs.h"
#include <fstream>
#include <nlohmann/json.hpp>

#include "clustering/AHC.h"

struct MergeStep;

std::string readFile(const std::string &init_file_path = "./resources/*", const std::vector<std::string> &file_types = {});

void exportToJsonAHC(std::vector<MergeStep> merge_history, const std::string &filename);

#endif // FILE_CONTROLLER_H
