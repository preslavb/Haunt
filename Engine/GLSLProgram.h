#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const std::string& t_vertex_shader_file_path, const std::string& t_fragment_shader_file_path);

	void LinkShaders();

	void AddAttribute(const std::string& t_attribute_name);

	GLint GetUniformLocation(const std::string& t_uniform_name);

	void Use();

	void Unuse();

private:
	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	int numberOfAttributes;

	void CompileShader(const std::string& t_file_path, GLuint id);
};

