#pragma once

namespace AAEngine {

#define AA_NUM_SHADER_TYPES 2

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
		* Pure virtual GetName function to get the name of the Shader.
		* 
		* @returns Name of the Shader.
		*/
		virtual std::string GetName() = 0;

		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param ShaderName - Name of the Shader
		* @param VertexShaderSource - std::string of the Vertex Shader Code.
		* @param FragmentShaderSource - std::string of the Fragment Shader Code.
		* 
		* @returns Pointer Ref to the Shader that was created
		*/
		static TSharedPtr<IShader> Create(const std::string& ShaderName, const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param ShaderFilePath - Path to the shader file
		* 
		* @returns Pointer Ref to the Shader that was created
		*/
		static TSharedPtr<IShader> Create(const std::string& ShaderFilePath);
		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param ShaderName - Name of the Shader
		* @param ShaderFilePath - Path to the shader file
		*
		* @returns Pointer Ref to the Shader that was created
		*/
		static TSharedPtr<IShader> Create(const std::string& ShaderName, const std::string& ShaderFilePath);
		static TSharedPtr<IShader> Create(std::string&& ShaderName, const std::string& ShaderFilePath);


		static std::string ExtractShaderNameFromFilePath(const std::string& ShaderFilePath)
		{
			auto LastSlash = ShaderFilePath.find_last_of("/\\");
			LastSlash = LastSlash == std::string::npos ? 0 : LastSlash + 1;
			auto DotAfterSlash = ShaderFilePath.rfind('.');
			return ShaderFilePath.substr(LastSlash, (DotAfterSlash == std::string::npos ? ShaderFilePath.size() : DotAfterSlash) - LastSlash);
		}
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

	/*
	* Platform and API independent Shader Library Class that stores all the Shaders for AA Engine.
	*/
	class CShaderLibrary
	{
	public:

		/*
		* Function to add a shader to the Shader Library.
		* 
		* @param ShaderName - Name of the Shader to add to the Library.
		* @param NewShader - Shader Ref to add to the Library.
		*/
		void AddShader(const std::string& ShaderName, const TSharedPtr<IShader>& NewShader);
		/*
		* Function to add a shader to the Shader Library.
		*
		* @param NewShader - Shader Ref to add to the Library.
		*/
		void AddShader(const TSharedPtr<IShader>& NewShader);

		/*
		* Function to load a shader into the Shader Library based on Vertex and Fragment Source code as String.
		*
		* @param ShaderName - Name of the Shader to add to the Library.
		* @param VertexShaderSource - std::string of the Vertex Shader Code.
		* @param FragmentShaderSource - std::string of the Fragment Shader Code.
		* 
		* @returns Shader Ref to the Loaded shader.
		*/
		TSharedPtr<IShader> LoadShader(const std::string& ShaderName, const std::string& VertexSource, const std::string& FragmentSource);
		/*
		* Function to load a shader into the Shader Library based on FilePath.
		*
		* @param ShaderName - Name of the Shader to add to the Library.
		* @param FilePath - std::string of the Path to the Shader.
		*
		* @returns Shader Ref to the Loaded shader.
		*/
		TSharedPtr<IShader> LoadShader(const std::string& ShaderName, const std::string& FilePath);
		/*
		* Function to load a shader into the Shader Library based on FilePath, Shader Name will be file name.
		*
		* @param FilePath - std::string of the Path to the Shader.
		*
		* @returns Shader Ref to the Loaded shader.
		*/
		TSharedPtr<IShader> LoadShader(const std::string& FilePath);

		/*
		* Function to get a Shader from the Shader Library by Shader Name
		*
		* @param ShaderName - Name of the Shader to get from the Library.
		*
		* @returns Shader Ref to the Loaded shader.
		*/
		TSharedPtr<IShader> GetShader(const std::string& ShaderName);
		
		/*
		* Function to get a Shader from the Shader Library by Shader Name
		*
		* @param ShaderName - Name of the Shader to check in the Library.
		*
		* @returns true if Shader with Name exists false otherwise 
		*/
		bool Exists(const std::string& ShaderName);

	private:
		/*
		* Hash Map like structure to store Shaders based on their names.
		*/
		TMap<std::string, TSharedPtr<IShader>> ShaderLibrary;
	};


}