#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>
#include <GL/glew.h>

// Constructor
GLSLProgram::GLSLProgram(): programID(0), vertexShaderID(0), fragmentShaderID(0), numberOfAttributes(0)
{
}

// Destructor
GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string& t_vertex_shader_file_path,	const std::string& t_fragment_shader_file_path)
{
	// Create a new program id for our new shader program
	programID = glCreateProgram();
	
	// Create a gl vertex shader and store the ID in the program
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	// The shader could not be created so crash out of the program
	if (!vertexShaderID)
	{
		fatalError("Vertex shader couldn't be created");
	}

	// Create a gl fragment shader and store the ID in the program
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// The shader could not be created so crash out of the program
	if (!fragmentShaderID)
	{
		fatalError("Fragment shader couldn't be created");
	}

	// Compile and populate the two shaders with the paths specified
	CompileShader(t_vertex_shader_file_path, vertexShaderID);
	CompileShader(t_fragment_shader_file_path, fragmentShaderID);
}

void GLSLProgram::LinkShaders()
{
	// Enable the two shaders in the GL state machine and attach them to the programID
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	// Link the two shaders into one GLSL program
	glLinkProgram(programID);

	// Check the link
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

	// Linking failed so throw an error with the information provided
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

	// Detach the shaders from the state machine and the program
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	// The program now contains the ids of both the shaders, so delete them from GL
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLSLProgram::AddAttribute(const std::string& t_attribute_name)
{
	// Bind the attribute of the corresponding order and name
	glBindAttribLocation(programID, numberOfAttributes++, t_attribute_name.c_str());
}

GLint GLSLProgram::GetUniformLocation(const std::string& t_uniform_name)
{
	// Try and find the location of the uniform in the shader
	GLint location = glGetUniformLocation(programID, t_uniform_name.c_str());

	// The location could not be found, so exit with an error
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + t_uniform_name + " could not be found");
	}

	return location;
}

void GLSLProgram::Use()
{
	// Enable the GLSL program for drawing
	glUseProgram(programID);

	// Enable the attributes bound to the program
	for (int i = 0; i < numberOfAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	// Disable drawing with this shader program
	glUseProgram(0);

	// Disable all attributes linked to this program
	for (int i = 0; i < numberOfAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::CompileShader(const std::string& t_file_path, GLuint t_id)
{
	// Create a sub-program for storing the compiled shader
	GLuint program = glCreateProgram();

	// Use the input file stream to load in the contents of the shader at the specified filepath
	std::ifstream file(t_file_path);

	// File path didn't return a file, so break out with an error
	if (file.fail())
	{
		perror(t_file_path.c_str());
		fatalError("Failed to " + t_file_path);
	}

	// Initialize the needed information storage
	std::string fileContents = "";
	std::string line;

	// Feed the current file lines into the file contents variable
	while (std::getline(file, line))
	{
		fileContents += line + "\n";
	}

	// Stop reading form the file and close the stream
	file.close();

	// Store the contents as a C style string
	const char* contentsPtr = fileContents.c_str();

	// Feed the shader source code into OpenGL
	glShaderSource(t_id, 1, &contentsPtr, nullptr);

	// Compile the previously fed string of code
	glCompileShader(t_id);

	// Check whether the compilation was successful
	GLint success = 0;
	glGetShaderiv(t_id, GL_COMPILE_STATUS, &success);

	// The compilation was unsuccessful, so display the compile error 
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

