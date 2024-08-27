#include "texture.h"
#include "stb_image.h"

Texture::Texture(const char *imageSrc, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    _type = texType;

    int imgWidth, imgHeight, numColChanells;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgBytes = stbi_load(imageSrc, &imgWidth, &imgHeight, &numColChanells, 0);

    glGenTextures(1, &_ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(_type, _ID);
    
	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_type, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, imgBytes);
	glGenerateMipmap(_type);

	stbi_image_free(imgBytes);
	glBindTexture(_type, 0);
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
    GLuint texUniID = glGetUniformLocation(shader._ID, uniform);
	shader.Activate();

	glUniform1i(texUniID, unit);
}

void Texture::Bind()
{
    glBindTexture(_type, _ID);
}

void Texture::Unbind()
{
    glBindTexture(_type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &_ID);
}
