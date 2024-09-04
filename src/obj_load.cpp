#include "obj_load.h"

struct Material {
    std::string name;
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

inline std::vector<Material> loadMaterials(const char *mtlPath) {
    std::ifstream mtlFile(mtlPath);

    std::vector<Material> materials;
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
                Material material = {matName, matColor};
                materials.push_back(material);

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
    Material material = {matName, matColor};
    materials.push_back(material);

    return materials;
}

Material getMaterial(const std::string &name, const std::vector<Material> &materials) {
    for (auto &material: materials) {
        if (material.name == name) {
            return material;
        }
    }
    return Material{};
}

std::vector<Mesh> meshesFromFile(const char *objPath) {
    std::ifstream objFile(objPath);

    std::vector<Mesh> meshes;

    std::string meshName;
    std::vector<Vertex> meshVertices;
    std::vector<GLuint> meshIndices;
    bool skipMeshCreation = true;

    int indicesDelta = 1;

    std::vector<Material> materials;
    std::unordered_map<std::string, Material> materialMap;

    std::string line;
    while (std::getline(objFile, line)) {
        trimLeadingWhitespace(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::vector<std::string> lineSubstrings = splitString(line);

        if (lineSubstrings[0] == "mtllib") {
            std::vector<Material> loadedMaterials = loadMaterials(lineSubstrings[1].c_str());
            for (auto &material: loadedMaterials) {
                materials.push_back(material);
            }
        }

        if (lineSubstrings[0] == "g") {
            if (!skipMeshCreation) {
                Material material = materialMap[meshName];
                glm::vec3 color = material.color;

                meshes.emplace_back(meshVertices, meshIndices, color, meshName.c_str());

                indicesDelta += static_cast<int>(meshVertices.size());

                meshName.clear();
                meshVertices.clear();
                meshIndices.clear();
            }
            meshName = splitString(lineSubstrings[1], ':')[0];
            skipMeshCreation = false;
        }

        if (lineSubstrings[0] == "usemtl") {
            materialMap[meshName] = getMaterial(lineSubstrings[1], materials);
        }

        if (lineSubstrings[0] == "v") {
            meshVertices.push_back({
                glm::vec3(std::stof(lineSubstrings[1]), std::stof(lineSubstrings[2]), std::stof(lineSubstrings[3]))
            });
        }

        if (lineSubstrings[0] == "f") {
            for (int i = 1; i < 4; i++) {
                std::vector<std::string> vertexIndices = splitString(lineSubstrings[i], '/');
                meshIndices.push_back(std::stoi(vertexIndices[0]) - indicesDelta);
            }
        }
    }

    Material material = materialMap[meshName];
    meshes.emplace_back(meshVertices, meshIndices, material.color, meshName.c_str());

    return meshes;
}
