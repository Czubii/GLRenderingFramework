#include "texture.h"
#include "stb_image.h"

Texture::Texture(const char *imageSrc, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;

	int imgWidth, imgHeight, numColChanells;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *imgBytes = stbi_load(imageSrc, &imgWidth, &imgHeight, &numColChanells, 0);

	std::cout << "R: " << static_cast<int>(imgBytes[0]) 
			<< " G: " << static_cast<int>(imgBytes[1]) 
			<< " B: " << static_cast<int>(imgBytes[2]) 
			<< " A: " << static_cast<int>(imgBytes[3]) 
			<< std::endl;

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

Texture::Texture(const unsigned char &R,	///FIXME: curently alpha doesnt matter or it only works when combining multiple textures? look into this
				 const unsigned char &G,
				 const unsigned char &B,
				 const unsigned char &A)
{
	GLubyte texColor[4] = {R, G, B, A};

	type = GL_TEXTURE_2D;

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(type, ID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(type, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, texColor);

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
