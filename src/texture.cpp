#include "texture.h"
#include "stb_image.h"

Texture::Texture(const char *imageSrc, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;

    int imgWidth, imgHeight, numColChanells;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgBytes = stbi_load(imageSrc, &imgWidth, &imgHeight, &numColChanells, 0);

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(type, ID);
    
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(type, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, imgBytes);
	glGenerateMipmap(type);

	stbi_image_free(imgBytes);
	glBindTexture(type, 0);
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
    GLuint texUniID = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();

	glUniform1i(texUniID, unit);
}

void Texture::Bind()
{
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
