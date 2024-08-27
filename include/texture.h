#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "shaderClass.h"

class Texture{

public: 
    GLuint _ID;
    GLenum _type;


    Texture(const char* imageSrc, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    void texUnit(Shader shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();

};

#endif
