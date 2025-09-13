#include "../headerfiles/TextureClass.h"
#include <stb_image/stb_image.h>


uint16_t Texture::nrOfTextures = 0;

Texture::Texture(const char* texPath, GLint rgb_or_rgba)
{
	if (nrOfTextures >= 31)
		std::cout << "To many textures " << nrOfTextures << '\n';

	glGenTextures(1, &m_ID);
	glActiveTexture(GL_TEXTURE0 + nrOfTextures);
	nrOfTextures++;

	glBindTexture(GL_TEXTURE_2D, m_ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(texPath, &m_width, &m_height, &m_nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, rgb_or_rgba, m_width, m_height, 0, rgb_or_rgba, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << '\n';
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Init(const char* texPath, GLint rgb_or_rgba)
{
	if (nrOfTextures >= 31)
		std::cout << "To many textures " << nrOfTextures << '\n';

	glGenTextures(1, &m_ID);
	glActiveTexture(GL_TEXTURE0 + nrOfTextures);
	nrOfTextures++;

	glBindTexture(GL_TEXTURE_2D, m_ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(texPath, &m_width, &m_height, &m_nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, rgb_or_rgba, m_width, m_height, 0, rgb_or_rgba, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << '\n';
}