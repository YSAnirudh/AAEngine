#include "AA_PreCompiledHeaders.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace AAEngine {

	COpenGLShader::COpenGLShader(const std::string& VertexShaderSource, const std::string& FragmentShaderSource)
	{
		TArray<FShaderData> ShaderData(2);
		ShaderData.PushBack({ VertexShaderSource, EShaderType::SHT_Vertex });
		ShaderData.PushBack({ FragmentShaderSource, EShaderType::SHT_Fragment });
		CompileShaders(ShaderData);
	}

	COpenGLShader::COpenGLShader(const std::string& ShaderFilePath)
	{
		TArray<FShaderData> ShaderData = ParseShaderSourceIntoShaderData(ReadShaderSourceFromFile(ShaderFilePath));
		CompileShaders(ShaderData);
	}

	COpenGLShader::~COpenGLShader()
	{
		glDeleteProgram(ShaderProgram);
	}

	void COpenGLShader::Bind()
	{
		glUseProgram(ShaderProgram);
	}

	void COpenGLShader::UnBind()
	{
		glUseProgram(0);
	}

	void COpenGLShader::UploadUniformInt(const std::string& UniformName, int Value)
	{
		GLuint Location = glGetUniformLocation(ShaderProgram, UniformName.c_str());
		glUniform1i(Location, Value);
	}

	void COpenGLShader::UploadUniformVec3(const std::string& UniformName, const FVector3f& Value)
	{
		GLuint Location = glGetUniformLocation(ShaderProgram, UniformName.c_str());
		glUniform3f(Location, Value.X, Value.Y, Value.Z);
	}

	void COpenGLShader::UploadUniformVec4(const std::string& UniformName, const FVector4f& Value)
	{
		GLuint Location = glGetUniformLocation(ShaderProgram, UniformName.c_str());
		glUniform4f(Location, Value.X, Value.Y, Value.Z, Value.W);
	}

	void COpenGLShader::UploadUniformMat4(const std::string& UniformName, const FMatrix44f& Value)
	{
		GLuint Location = glGetUniformLocation(ShaderProgram, UniformName.c_str());
		glUniformMatrix4fv(Location, 1, GL_FALSE, Value.MLin);
	}

	std::string COpenGLShader::ReadShaderSourceFromFile(const std::string& ShaderFilePath)
	{
		std::ifstream FileToRead(ShaderFilePath, std::ios::in | std::ios::binary);

		if (FileToRead)
		{
			std::string Result;
			FileToRead.seekg(0, std::ios::end);
			Result.resize(FileToRead.tellg());
			FileToRead.seekg(0, std::ios::beg);
			FileToRead.read(&Result[0], Result.size());
			FileToRead.close();
			return Result;
		}
		AA_CORE_LOG(Error, "Couldn't Open File - %s", ShaderFilePath.c_str());
		return "";
	}

	// TO DO Replace with HashMap
	TArray<FShaderData> COpenGLShader::ParseShaderSourceIntoShaderData(const std::string& ShaderSource)
	{
		TArray<FShaderData> ShaderDataArray;
		const char* StringMatch = "#aa_shader_type";
		size_t ShaderTypeLength = strlen(StringMatch);

		size_t TypePos = ShaderSource.find(StringMatch, 0);

		while (TypePos != std::string::npos)
		{
			// TO DO: Make this Flexible
			// TO DO: Make sure there is only one instance of a shader type (Solution: Hash Map)
			//size_t LinePos = ShaderSource.find_first_of("#aa_shader_type", TypePos);
			size_t LinePos = ShaderSource.find_first_of("\r\n", TypePos);

			AA_CORE_ASSERT(int(LinePos != std::string::npos), "AA Shader Syntax Error!");

			size_t ShaderNamePos = TypePos + ShaderTypeLength + 1;

			std::string ShaderName = ShaderSource.substr(ShaderNamePos, LinePos - ShaderNamePos);

			EShaderType CurrShaderType = AAShaderStringToEnum(ShaderName);
			AA_CORE_ASSERT(int(CurrShaderType != EShaderType::SHT_None), "Invalid Shader Type specified!");

			size_t NextLinePos = ShaderSource.find_first_not_of("\r\n", LinePos);
			TypePos = ShaderSource.find(StringMatch, NextLinePos);
			std::string SingleShaderSource = ShaderSource.substr(NextLinePos, TypePos - (NextLinePos == std::string::npos ? ShaderSource.size() - 1 : NextLinePos));

			// TO DO: First allocate then assign. not emplace/push
			ShaderDataArray.PushBack({ SingleShaderSource, CurrShaderType });
			AA_CORE_LOG(Info, "%s", SingleShaderSource.c_str());
		}

		return ShaderDataArray;
	}

	void COpenGLShader::CompileShaders(const TArray<FShaderData>& ShaderDataArray)
	{
		GLenum Program = glCreateProgram();
		TArray<GLenum> ShaderIDs(ShaderDataArray.Num());
		for (const FShaderData& ShaderData : ShaderDataArray)
		{
			uint32_t ShaderCode = glCreateShader(AAShaderEnumToAPIEnum(ShaderData.ShaderType));

			const GLchar* Source = ShaderData.ShaderSource.c_str();
			glShaderSource(ShaderCode, 1, &Source, 0);

			glCompileShader(ShaderCode);

			GLint CompileStatus;
			glGetShaderiv(ShaderCode, GL_COMPILE_STATUS, &CompileStatus);

			if (CompileStatus == GL_FALSE)
			{
				GLint MaxLength = 0;
				glGetShaderiv(ShaderCode, GL_INFO_LOG_LENGTH, &MaxLength);

				TArray<GLchar> Message(MaxLength);

				glGetShaderInfoLog(ShaderCode, MaxLength, &MaxLength, &Message[0]);

				glDeleteShader(ShaderCode);

				AA_CORE_LOG(Error, "Shader Info: %s", Message.Data());
				AA_CORE_ASSERT(false, AAShaderEnumToString(ShaderData.ShaderType).append("Shader Compilation Error!").c_str());
				break;
			}
			glAttachShader(Program, ShaderCode);
			ShaderIDs.PushBack(ShaderCode);
		}

		// PROGRAM CREATION AND LINKING
		ShaderProgram = Program;

		glLinkProgram(ShaderProgram);

		GLint ShaderLinkStatus;
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ShaderLinkStatus);

		if (ShaderLinkStatus == GL_FALSE)
		{
			GLint MaxLength = 0;
			glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &MaxLength);

			TArray<GLchar> Message(MaxLength);

			glGetProgramInfoLog(ShaderProgram, MaxLength * sizeof(GLchar), &MaxLength, &Message[0]);

			glDeleteProgram(ShaderProgram);

			for (GLenum Code : ShaderIDs)
			{
				glDeleteShader(Code);
			}

			AA_CORE_LOG(Error, "Shader Program Info: %s", Message.Data());
			AA_CORE_ASSERT(false, "Shader Linking Error!");
			return;
		}

		for (GLenum Code : ShaderIDs)
		{
			glDetachShader(ShaderProgram, Code);
		}
	}

	unsigned int COpenGLShader::AAShaderEnumToAPIEnum(EShaderType ShaderType)
	{
		switch (ShaderType)
		{
		case EShaderType::SHT_Vertex:
			return GL_VERTEX_SHADER;
		case EShaderType::SHT_Fragment:
			return GL_FRAGMENT_SHADER;
		case EShaderType::SHT_None:
		default:
			break;
		}
		return 0;
	}
}