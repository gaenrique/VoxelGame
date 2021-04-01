#include "Shader.h"

#include <GL/glew.h>

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
	GetSourceCode(vertexPath.str());
	GetSourceCode(fragmentPath.str());
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

Shader::~Shader()
{

}

void Shader::Bind() const
{

}

void Shader::Unbind() const
{

}