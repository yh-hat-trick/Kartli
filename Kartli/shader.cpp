#include "shader.h"
#include <iostream>
#include <fstream>

std::string Shader::load(std::string path)
{
	std::string line, allLines;
	std::ifstream s;
	s.open(path);
	if (s.is_open())
	{
		int length;
		// Find the length
		s.seekg(0, std::ios::end);
		length = s.tellg();
		
		// Read the file
		char* src = new char[length];
		s.seekg(0, std::ios::beg);
		s.read(src, length);
		src[s.gcount()] = '\0';
		allLines = src;
		delete src;
		s.close();
	}
	else
	{
		std::cerr << "ERROR::COULD NOT READ SHADER FILE " << path << std::endl;
	}
	return allLines;
}

Shader::Shader(std::string name)
{
	std::string vString = load(name + ".vs");
	std::string fString = load(name + ".fs");
	const char* vChars = vString.c_str();
	const char* fChars = fString.c_str();
	
	unsigned int vs, fs;
	int  success;
	char infoLog[512];

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vChars, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << vChars << std::endl;
	}

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fs, 1, &fChars, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << fChars << std::endl;
	}

	shaderID = glCreateProgram();

	glAttachShader(shaderID, vs);
	glAttachShader(shaderID, fs);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_AND_COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::bind()
{
	glUseProgram(shaderID);
}

Shader::~Shader()
{


}