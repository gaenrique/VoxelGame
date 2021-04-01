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
	void CompileShaders(const std::vector<unsigned int>& shaders, const std::vector<std::string>& source);
	void LinkShaders(const std::vector<unsigned int>& shaders);
};