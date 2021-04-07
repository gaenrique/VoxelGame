#include "Shader.h"

#include <GL/glew.h>

#include "GLError.h"

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::ostringstream vertexPath;
	std::ostringstream fragmentPath;
	// Relative path from exe file to Shaders file
	// This enables the constructor arguments to simply be the name of the
	// shader file
	vertexPath << "../../../../src/Renderer/Shaders/" << vertex;
	fragmentPath << "../../../../src/Renderer/Shaders/" << fragment;

	std::string vertexSource = GetSourceCode(vertexPath.str());
	std::string fragmentSource = GetSourceCode(fragmentPath.str());

	CompileShader(vertexShader, vertexSource);
	CompileShader(fragmentShader, fragmentSource);
	LinkShaders(vertexShader, fragmentShader);
}

// Parses shader file and returns string containing file contents
std::string Shader::GetSourceCode(const std::string& filepath)
{
	std::ostringstream stringStream;
	std::ifstream fileStream(filepath);
	std::string line;
	while (std::getline(fileStream, line))
	{
		stringStream << line << "\n";
	}
	return stringStream.str();
}

void Shader::CompileShader(unsigned int shader, const std::string& source)
{
	// Get strings for glShaderSource.
	const GLchar* sourceString = (const GLchar*)source.c_str();
	GLCall(glShaderSource(shader, 1, &sourceString, 0));

	GLCall(glCompileShader(shader));

	GLint isCompiled = 0;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		GLCall(glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]));

		std::cout << "Error found in shader:" << std::endl;
		// Provide the infolog in whatever manor you deem best.
		for (GLchar c : errorLog)
		{
			std::cout << c;
		}
		std::cout << std::endl;
		// Exit with failure.
		GLCall(glDeleteShader(shader)); // Don't leak the shader.
		return;
	}
	
	std::cout << "Shader compiled succesfully!" << std::endl;
}

void Shader::LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);

	// Link our program
	glLinkProgram(m_RendererID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_RendererID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_RendererID, vertexShader);
	glDetachShader(m_RendererID, fragmentShader);

	std::cout << "Shaders linked successfully!" << std::endl;
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}