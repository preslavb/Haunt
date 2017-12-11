#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>
#include <GL/glew.h>


GLSLProgram::GLSLProgram(): programID(0), vertexShaderID(0), fragmentShaderID(0), numberOfAttributes(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string& t_vertex_shader_file_path,	const std::string& t_fragment_shader_file_path)
{
	programID = glCreateProgram();
	
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (!vertexShaderID)
	{
		fatalError("Vertex shader couldn't be created");
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!fragmentShaderID)
	{
		fatalError("Fragment shader couldn't be created");
	}

	CompileShader(t_vertex_shader_file_path, vertexShaderID);
	CompileShader(t_fragment_shader_file_path, fragmentShaderID);
}

void GLSLProgram::LinkShaders()
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link");
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLSLProgram::AddAttribute(const std::string& t_attribute_name)
{
	glBindAttribLocation(programID, numberOfAttributes++, t_attribute_name.c_str());
}

GLint GLSLProgram::GetUniformLocation(const std::string& t_uniform_name)
{
	GLint location = glGetUniformLocation(programID, t_uniform_name.c_str());

	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + t_uniform_name + " could not be found");
	}

	return location;
}

void GLSLProgram::Use()
{
	glUseProgram(programID);

	for (int i = 0; i < numberOfAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	glUseProgram(0);

	for (int i = 0; i < numberOfAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::CompileShader(const std::string& t_file_path, GLuint t_id)
{
	GLuint program = glCreateProgram();

	std::ifstream file(t_file_path);
	if (file.fail())
	{
		perror(t_file_path.c_str());
		fatalError("Failed to " + t_file_path);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(file, line))
	{
		fileContents += line + "\n";
	}

	file.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(t_id, 1, &contentsPtr, nullptr);

	glCompileShader(t_id);

	GLint success = 0;
	glGetShaderiv(t_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(t_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		__glewGetShaderInfoLog(t_id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(t_id);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader failed to compile");

		return;
	}
}

