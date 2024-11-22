#include "FileController.h"

std::string readFile(const std::string &init_file_path, const std::vector<std::string> &file_types)
{
    // Convertir std::vector<std::string> a const char*[]
    std::vector<const char *> filter_patterns;
    for (const auto &file_type : file_types)
        filter_patterns.push_back(file_type.c_str());

    // Llamar a tinyfd_openFileDialog
    const char *file_path = tinyfd_openFileDialog(
        "Select a file: ",
        init_file_path.c_str(),
        filter_patterns.size(),
        filter_patterns.empty() ? nullptr : filter_patterns.data(),
        nullptr,
        0);

    // Retornar la ruta seleccionada o una cadena vacía
    return file_path ? std::string(file_path) : "";
}
