#include "AA_PreCompiledHeaders.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace AAEngine {

	COpenGLShader::COpenGLShader(const std::string& VertexShaderSource, const std::string& FragmentShaderSource)
	{
		// VERTEX SHADER
		uint32_t VertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* VertexSource = VertexShaderSource.c_str();
		glShaderSource(VertexShader, 1, &VertexSource, 0);

		glCompileShader(VertexShader);

		GLint VertexCompileStatus;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &VertexCompileStatus);
		if (VertexCompileStatus == GL_FALSE)
		{
			GLint MaxLength = 0;
			glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &MaxLength);

			TArray<GLchar> Message(MaxLength);

			glGetShaderInfoLog(VertexShader, MaxLength, &MaxLength, &Message[0]);

			glDeleteShader(VertexShader);

			AA_CORE_LOG(Error, "Vertex Shader Info: %s", Message.Data());
			AA_CORE_ASSERT(false, "Vertex Shader Compilation Error!");
			return;
		}

		// FRAGMENT SHADER
		uint32_t FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* FragmentSource = FragmentShaderSource.c_str();
		glShaderSource(FragmentShader, 1, &FragmentSource, 0);

		glCompileShader(FragmentShader);

		GLint FragmentCompileStatus;
		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &FragmentCompileStatus);
		if (FragmentCompileStatus == GL_FALSE)
		{
			GLint MaxLength = 0;
			glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &MaxLength);

			TArray<GLchar> Message(MaxLength);

			glGetShaderInfoLog(FragmentShader, MaxLength * sizeof(GLchar), &MaxLength, &Message[0]);

			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			AA_CORE_LOG(Error, "Fragment Shader Info: %s", Message.Data());
			AA_CORE_ASSERT(false, "Fragment Shader Compilation Error!");
			return;
		}

		// PROGRAM CREATION AND LINKING
		ShaderProgram = glCreateProgram();

		glAttachShader(ShaderProgram, VertexShader);
		glAttachShader(ShaderProgram, FragmentShader);

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

			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			AA_CORE_LOG(Error, "Shader Program Info: %s", Message.Data());
			AA_CORE_ASSERT(false, "Shader Linking Error!");
			return;
		}

		glDetachShader(ShaderProgram, VertexShader);
		glDetachShader(ShaderProgram, FragmentShader);
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
}