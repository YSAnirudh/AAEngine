#pragma once

#include "Core/Renderer/Texture.h"

namespace AAEngine {

	/*struct FOpenGLTextureParams
	{

	};*/

	/*
	* OpenGL specific Texture2D Class.
	*/
	class COpenGLTexture2D : public ITexture2D
	{
	public:
		/*
		* Constructor that takes in a file path to create the texture 2D
		* 
		* @param FilePath - Path to the texture file
		*/
		COpenGLTexture2D(const std::string& FilePath);

		/*
		* Overriden virtual destructor
		*/
		virtual ~COpenGLTexture2D() override;

		/*
		* Overriden virtual getter for width of the Texture.
		*
		* @returns Width of the Texture
		*/
		virtual uint32_t GetWidth() const override
		{
			return Width;
		}

		/*
		* Overriden virtual getter for height of the Texture.
		*
		* @returns Height of the Texture
		*/
		virtual uint32_t GetHeight() const override
		{
			return Height;
		}

		/*
		* Overriden virtual Bind function to bind the texture to a slot.
		*
		* @param Slot - Slot in the Shader to bind to.
		*/
		virtual void Bind(uint32_t Slot = 0) const override;

		/*
		* Getter for Texture ID.
		*
		* @returns ID of the Texture
		*/
		uint32_t GetTextureID() const
		{
			return TextureID;
		}

	private:
		/*
		* Function to create a GL Texture 2D with parameters
		* 
		* @param Levels - Num of Levels for the texture
		* @param Format - Format of the Texture - GL_RGB8 / GLRGBA8
		* @param FilterType - Filter for Minification and Magnification
		* 
		* @returns TextureID of the created texture
		*/
		uint32_t CreateOpenGLTexture2D(int Levels, uint32_t Format, int FilterType);
		/*
		* Function to load a GL Texture 2D with parameters into OpenGL
		*
		* @param Level - Level of the texture to load
		* @param XOffset - Offset from bottom left X coordinate
		* @param YOffset - Offset from bottom left Y coordinate
		* @param InWidth - Width of the Texture to load
		* @param InHeight - Height of the Texture to load
		* @param Format - Format of the Texture - GL_RGB8 / GLRGBA8
		* @param Data - void* for the Texture Data we get from loading the texture image file.
		*/
		void LoadIntoOpenGL(int Level, int XOffset, int YOffset, int InWidth, int InHeight, uint32_t Format, const void* Data);

	private:
		// Only for debugging. TO DO: Shift to asset manager when that is setup.
		/*
		* File Path to the texture file
		*/
		std::string Path;

		/*
		* Width of the Texture
		*/
		uint32_t Width;
		/*
		* Height of the Texture
		*/
		uint32_t Height;
		/*
		* ID for the Texture
		*/
		uint32_t TextureID{};

	};
}