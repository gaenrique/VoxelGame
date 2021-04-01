#include "Shader.h"

#include <GL/glew.h>

#include "GLError.h"

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
	std::vector<unsigned int> shaders;
	shaders.push_back(glCreateShader(GL_VERTEX_SHADER));
	shaders.push_back(glCreateShader(GL_FRAGMENT_SHADER));
	std::ostringstream vertexPath;
	std::ostringstream fragmentPath;
	// Relative path from exe file to Shaders file
	// This enables the constructor arguments to simply be the name of the
	// shader file
	vertexPath << "../../../../src/Renderer/Shaders/" << vertex;
	fragmentPath << "../../../../src/Renderer/Shaders/" << fragment;
	std::vector<std::string> source;
	source.push_back(GetSourceCode(vertexPath.str()));
	source.push_back(GetSourceCode(fragmentPath.str()));
	CompileShaders(shaders, source);
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

void Shader::CompileShaders(const std::vector<unsigned int>& shaders, const std::vector<std::string>& source)
{
	for (int i = 0; i < shaders.size(); i++)
	{
		// Shader string used for error output in order to know which shader
		// contains the rror
		std::string shaderType = (i == 0) ? "Vertex Shader" : "Fragment Shader";
		// Get strings for glShaderSource.
		const GLchar* sourceString = (const GLchar*)source[i].c_str();
		GLCall(glShaderSource(shaders[i], 1, &sourceString, 0));

		GLCall(glCompileShader(shaders[i]));

		GLint isCompiled = 0;
		GLCall(glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &isCompiled));
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			GLCall(glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &maxLength));

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			GLCall(glGetShaderInfoLog(shaders[i], maxLength, &maxLength, &errorLog[0]));

			// Provide the infolog in whatever manor you deem best.
			for (GLchar c : errorLog)
			{
				std::cout << "Error found in " << shaderType << std::endl;
				std::cout << c;
			}
			std::cout << std::endl;
			// Exit with failure.
			GLCall(glDeleteShader(shaders[i])); // Don't leak the shader.
			return;
		}
		
		std::cout << shaderType << " compiled succesfully!" << std::endl;
	}
}

void Shader::LinkShaders(const std::vector<unsigned int>& shaders)
{

}

Shader::~Shader()
{
}

void Shader::Bind() const
{

}

void Shader::Unbind() const
{

}