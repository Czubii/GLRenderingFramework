#include "obj_load.h"

struct Material {
    glm::vec3 color;
};

inline void trimLeadingWhitespace(std::string &str) {
    str.erase(str.begin(), std::find_if_not(str.begin(), str.end(), [](unsigned char ch) {
        return std::isspace(ch);
    }));
}

inline std::vector<std::string> splitString(const std::string &str, const char separator = ' ') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, separator)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

inline std::unordered_map<std::string, Material> loadMaterials(const char *mtlPath) {
    std::ifstream mtlFile(mtlPath);

    std::unordered_map<std::string, Material> materialMap;
    bool skipCreatingMaterial = true;

    std::string matName;
    glm::vec3 matColor = glm::vec3(0.0f, 0.0f, 0.0f);

    std::string line;
    while (std::getline(mtlFile, line)) {
        trimLeadingWhitespace(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::vector<std::string> lineSubstrings = splitString(line);

        if (lineSubstrings[0] == "newmtl") {
            if (!skipCreatingMaterial) {
                materialMap[matName] = {matColor};

                matName.clear();
                matColor = glm::vec3(0.0f, 0.0f, 0.0f);
            }
            matName = lineSubstrings[1];

            skipCreatingMaterial = false;
        } else if (lineSubstrings[0] == "Kd") {
            matColor = glm::vec3(std::stof(lineSubstrings[1]), std::stof(lineSubstrings[2]),
                                 std::stof(lineSubstrings[3]));
        }
    }
    materialMap[matName] = {matColor};

    return materialMap;
}

Mesh meshFromFile(const char *objPath) {
    //TODO: Move to mesh class as constructor
    std::ifstream objFile(objPath);

    std::string meshName;
    std::vector<glm::vec3> v;
    std::vector<glm::vec3> vn;
    std::vector<Vertex> meshVertices;

    std::vector<Material> materials;
    std::unordered_map<std::string, Material> materialMap;
    Material *currentMaterial;

    std::string line;
    while (std::getline(objFile, line)) {
        trimLeadingWhitespace(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::vector<std::string> lineSubstrings = splitString(line);

        if (lineSubstrings[0] == "mtllib") {
            materialMap = loadMaterials(lineSubstrings[1].c_str());
        }

        if (lineSubstrings[0] == "usemtl") {
            currentMaterial = &materialMap[lineSubstrings[1]];
        }

        if (lineSubstrings[0] == "v") {
            v.push_back({
                glm::vec3(std::stof(lineSubstrings[1]), std::stof(lineSubstrings[2]), std::stof(lineSubstrings[3]))
            });
        }
        if (lineSubstrings[0] == "vn") {
            vn.push_back({
                glm::vec3(std::stof(lineSubstrings[1]), std::stof(lineSubstrings[2]), std::stof(lineSubstrings[3]))
            });
        }

        if (lineSubstrings[0] == "f") {
            for (int i = 1; i < 4; i++) {
                std::vector<std::string> vertexIndices = splitString(lineSubstrings[i], '/');
                meshVertices.push_back({
                    v[std::stoi(vertexIndices[0]) - 1], vn[std::stoi(vertexIndices[2]) - 1], currentMaterial->color
                });
            }
        }
    }


    return {meshVertices, meshName.c_str()};
}
