#pragma once

#include <string>

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
};