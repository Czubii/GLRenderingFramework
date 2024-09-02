#ifndef CHUNK_CLASS
#define CHUNK_CLASS

#include <vector>
#include <glm.hpp>
#include <mesh.h>
#include <gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <gtc/matrix_transform.hpp>

#define CHUNK_DIM_X 16
#define CHUNK_DIM_Z 16
#define CHUNK_DIM_Y 128

class Chunk {
public:
    int chunkPosX = 0;
    int chunkPosY = 0;

    Mesh voxelMesh;

    VBO instanceTransformationsVBO;



    unsigned char chunkDataMatrix[CHUNK_DIM_X][CHUNK_DIM_Y][CHUNK_DIM_Z] = {0};

    Chunk();

    void draw(Shader& shader, const Camera& camera, DrawMode mode = DrawMode::DEFAULT);

private:
    int m_numVoxels = 0;
    std::vector<glm::mat4> m_instanceTranslationMatrices;

    void generateVoxelMesh();
    void generateInstanceTransformationMatrix();

    ///@brief updates instance VBO with m_instanceTranslationMatrix
    void updateInstanceVBO() const; //TODO updateInstanceVBO() func

    void linkInstanceVBO();
};


#endif
