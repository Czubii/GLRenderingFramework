#ifndef OBJ_LOAD_H
#define OBJ_LOAD_H

#include "mesh.h"
#include <fstream>
#include <string>
#include <algorithm> // for std::find_if_not
#include <cctype>    // for std::isspace
#include <iostream>

/// @brief Load a mesh from an obj file and its corresponding mtl file
std::vector<Mesh> meshesFromFile(const char *objPath);

#endif //OBJ_LOAD_H
