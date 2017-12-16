#pragma once
#include <string>
#include <GL/glew.h>

// A program to run GLSL shader code
class GLSLProgram
{
public:
	// Constructor and destructor
	GLSLProgram();
	~GLSLProgram();

	// Compile the shaders with the file names specified
	void CompileShaders(const std::string& t_vertex_shader_file_path, const std::string& t_fragment_shader_file_path);

	// Link the vertex and fragment shader together into one program
	void LinkShaders();

	// Add an attribute to the program (should be done for each required attribute of the program for maximum compatibility)
	void AddAttribute(const std::string& t_attribute_name);

	// Returns the location of the uniform in the shader program
	GLint GetUniformLocation(const std::string& t_uniform_name);

	// Use this program for drawing
	void Use();

	// Stop using the program for drawing
	void Unuse();

private:
	// The ID of the program
	GLuint programID;

	// The seperate IDs for the vertex and fragment shaders
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	// How many attributes have been registered (attributes need to be registered in the correct order because of this)
	int numberOfAttributes;

	// Compiles a vertex or fragment shader
	void CompileShader(const std::string& t_file_path, GLuint id);
};

