#pragma once

#include <string>
#include <vector>

class Shader
{
public:

	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();
	
	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;

	std::string GetSourceCode(const std::string& filepath);
	void CompileShader(unsigned int shader, const std::string& source);
	void LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
};