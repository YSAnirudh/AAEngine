#include "AA_PreCompiledHeaders.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace AAEngine {
	COpenGLTexture2D::COpenGLTexture2D(const std::string& FilePath)
		: Path(FilePath)
	{
		int OutWidth, OutHeight, OutChannels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* TextureData = stbi_load(FilePath.c_str(), &OutWidth, &OutHeight, &OutChannels, 0);

		AA_CORE_ASSERT(TextureData, "Cannot open and load Texture! Texture data is nullptr");

		Width = OutWidth;
		Height = OutHeight;
		uint32_t Format = 0;
		switch (OutChannels)
		{
		case 1:
			Format = GL_RED;
			break;
		case 3:
			Format = GL_RGB8;
			break;
		case 4:
			Format = GL_RGBA8;
			break;
		}
		TextureID = CreateOpenGLTexture2D(1, Format, GL_NEAREST);

		LoadIntoOpenGL(0, 0, 0, Width, Height, Format, TextureData);

		stbi_image_free(TextureData);
	}

	COpenGLTexture2D::~COpenGLTexture2D()
	{
		glDeleteTextures(1, &TextureID);
	}

	void COpenGLTexture2D::Bind(uint32_t Slot) const
	{
		glBindTextureUnit(Slot, TextureID);
	}

	uint32_t COpenGLTexture2D::CreateOpenGLTexture2D(int Levels, uint32_t Format, int FilterType)
	{
		uint32_t TexID;
		glCreateTextures(GL_TEXTURE_2D, 1, &TexID);
		glTextureStorage2D(TexID, Levels, Format, Width, Height);

		glTextureParameteri(TexID, GL_TEXTURE_MIN_FILTER, FilterType);
		glTextureParameteri(TexID, GL_TEXTURE_MAG_FILTER, FilterType);
		return TexID;
	}

	void COpenGLTexture2D::LoadIntoOpenGL(int Level, int XOffset, int YOffset, int InWidth, int InHeight, uint32_t Format, const void* Data)
	{
		glTextureSubImage2D(TextureID, Level, XOffset, YOffset, InWidth, InHeight, Format, GL_UNSIGNED_BYTE, Data);
	}
}