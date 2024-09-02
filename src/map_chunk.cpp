#include "map_chunk.h"

#include <cube.h>

Chunk::Chunk() {
    generateVoxelMesh();

    for (int z = 0; z < CHUNK_DIM_Z; z++) {
        if (z % 2 == 0)
            continue;

        for (int x = 0; x < CHUNK_DIM_X; x++) {
            if (x % 2 == 0)
                continue;


            for (int y = 0; y < CHUNK_DIM_Y; y++) {
                chunkDataMatrix[x][y][z] = 1;
                m_numVoxels++;
            }
        }
    }
    generateInstanceTransformationMatrix();
    updateInstanceVBO();
    linkInstanceVBO();
}

void Chunk::draw(Shader &shader, const Camera &camera, DrawMode mode) {
    voxelMesh.drawInstanced(shader, camera, m_numVoxels, mode);
}

void Chunk::generateVoxelMesh() {
    const auto voxelVertices = std::vector<Vertex>(std::begin(cube::vertices), std::end(cube::vertices));
    const auto voxelIndices = std::vector<GLuint>(std::begin(cube::indices), std::end(cube::indices));
    voxelMesh = Mesh(voxelVertices, voxelIndices, Texture(120, 40, 42));
}

void Chunk::generateInstanceTransformationMatrix() {

    m_instanceTranslationMatrices = std::vector<glm::mat4>{};
    for (int x = 0; x < CHUNK_DIM_X; x++) {
        for (int y = 0; y < CHUNK_DIM_Y; y++) {
            for (int z = 0; z < CHUNK_DIM_Z; z++) {
                if (chunkDataMatrix[x][y][z] == 0) {
                    continue;
                }

                auto translation = glm::mat4(1.0f);
                translation = glm::translate(translation, glm::vec3(x + chunkPosX, y + chunkPosY, z));

                m_instanceTranslationMatrices.push_back(translation);
            }
        }
    }
}

void Chunk::updateInstanceVBO() const {
    instanceTransformationsVBO.updateData(m_instanceTranslationMatrices.data(),
                                          sizeof(glm::mat4) * m_instanceTranslationMatrices.size());
}

void Chunk::linkInstanceVBO() {
    voxelMesh.VAO.Bind();
    instanceTransformationsVBO.Bind();

    // Assuming the model matrix is at layout locations 3, 4, 5, and 6
    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(3 + i);
        GL_CHECK_ERROR();
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4) * i));
        GL_CHECK_ERROR();
        glVertexAttribDivisor(3 + i, 1); // Update per instance
        GL_CHECK_ERROR();
    }


    voxelMesh.VAO.Unbind();
    instanceTransformationsVBO.Unbind();
}
