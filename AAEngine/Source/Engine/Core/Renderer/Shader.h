#pragma once

namespace AAEngine {

	/*
	* Enum indicating the Shader Types currently supported by AA Engine
	*/
	enum class EShaderType : uint8_t
	{
		SHT_None,
		SHT_Vertex,
		SHT_Fragment,
	};

	/*
	* Struct of data containing the Source code for the Shader along with it's type.
	* 
	* There can be only one shader type per IShader object
	*/
	struct FShaderData
	{
		FShaderData(const std::string& ShaderSrc, EShaderType ShType)
			: ShaderSource(ShaderSrc), ShaderType(ShType) {}
		FShaderData(EShaderType ShType, const std::string& ShaderSrc)
			: ShaderSource(ShaderSrc), ShaderType(ShType) {}
		std::string ShaderSource;
		EShaderType ShaderType;
	};

	/*
	* Platform and API independent Shader Interface to be implemented per platform/API and in the AAEngine.
	*/
	class IShader
	{
	public:
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~IShader() {}

		/*
		* Pure virtual Bind function to Bind the shader to the program.
		*/
		virtual void Bind() = 0;

		/*
		* Pure virtual UnBind function to UnBind the shader from the program.
		*/
		virtual void UnBind() = 0;

		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param VertexShaderSource - std::string of the Vertex Shader Code.
		* @param FragmentShaderSource - std::string of the Fragment Shader Code.
		*/
		static IShader* Create(const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param ShaderFilePath - Path to the shader file
		*/
		static IShader* Create(const std::string& ShaderFilePath);

	protected:

		/*
		* AA's native shader type string to Shader Type
		* 
		* @param ShaderType - std::string of the Type of Shader (Ex: vertex)
		* 
		* @returns Enum of the ShaderType
		*/
		FORCEINLINE EShaderType AAShaderStringToEnum(const std::string& ShaderType) const
		{
			if (ShaderType == "vertex")
			{
				return EShaderType::SHT_Vertex;
			}
			else if (ShaderType == "fragment" || ShaderType == "pixel")
			{
				return EShaderType::SHT_Fragment;
			}
			return EShaderType::SHT_None;
		}

		/*
		* AA's Shader Type Enum to native shader shader type string
		*
		* @param ShaderType - EShaderType of the Type of Shader (Ex: vertex)
		*
		* @returns std::string of the ShaderType
		*/
		FORCEINLINE std::string AAShaderEnumToString(const EShaderType& ShaderType) const
		{
			switch (ShaderType)
			{
			case EShaderType::SHT_Vertex:
				return "Vertex";
			case EShaderType::SHT_Fragment:
				return "Fragment / Pixel";
			case EShaderType::SHT_None:
			default:
				break;
			}
			return "Unknown Shader";
		}

		/*
		* Pure virtual Shader Enum to API specific enum function.
		* 
		* @param ShaderType - EShaderType Enum of the Type of Shader (Ex: EShaderType::SHT_Vertex)
		* 
		* @returns The unsigned int for the API specific shader enum (Ex: OpenGL - GL_VERTEX_SHADER)
		*/
		FORCEINLINE virtual unsigned int AAShaderEnumToAPIEnum(EShaderType ShaderType) = 0;
	};


}