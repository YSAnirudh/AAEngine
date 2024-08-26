#pragma once

#include "Core/Core.h"

namespace AAEngine {

	/*
	* Platform Independent Texture Class
	*/
	class ITexture
	{
	public:
		/*
		* Pure virtual destructor as we know we will derive from this class
		*/
		virtual ~ITexture() {}

		/*
		* Pure virtual getter for width of the Texture.
		* 
		* @returns Width of the Texture
		*/
		virtual uint32_t GetWidth() const = 0;
		/*
		* Pure virtual getter for height of the Texture.
		* 
		* @returns Height of the Texture
		*/
		virtual uint32_t GetHeight() const = 0;

		/*
		* Pure virtual Bind function to bind the texture to a slot.
		*
		* @param Slot - Slot in the Shader to bind to.
		*/
		virtual void Bind(uint32_t Slot = 0) const = 0;
	};

	/*
	* Platform Independent Texture2D Class which is an ITexture
	*/
	class ITexture2D : public ITexture
	{
	public:
		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param FilePath - Path to the texture file
		*
		* @returns A Platform indepentent Texture 2D Ref
		*/
		static TSharedPtr<ITexture2D> Create(const std::string& FilePath);
	};
}