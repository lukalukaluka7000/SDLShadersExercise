#include<fstream>
#include<vector>
#include "GLSLProgram.h"

#include<iostream>
#include"IOManager.h"


GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{
	//_programID=0
	//instead initialization lists -> gore
	//_vertexShaderID=0
	//_fragmentShaderID=0
}


GLSLProgram::~GLSLProgram()
{
	glUseProgram(0);
	if (_programID)
		glDeleteProgram(_programID);
	// kad ovo pozoves u maingame destruktoru mozda javi gresku
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}


void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {

	std::string vertSource;
	std::string fragSource;

	IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
	IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);


	compileShadersFromSource(vertSource.c_str(), fragSource.c_str());

}
void GLSLProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource) {
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	_programID = glCreateProgram();

	//open the files and read the data -> compile the shaders
	//opengl shader compilation
	//GLVERTEXX_SHADER, GL_FRAGMENT_SHADER
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (_vertexShaderID == 0) {
		std::cout << "Vertex Shader failed to be created!" << std::endl;
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (_fragmentShaderID == 0) {
		std::cout << "Fragment Shader failed to be created!" << std::endl;
	}

	compileShader(vertexSource, "Vertex File", _vertexShaderID);
	compileShader(fragmentSource, "Fragment File", _fragmentShaderID);
}
void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint id) {


	/*//load the code from files
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open" + filePath);
	}
	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}
	shaderFile.close();

	const char* contentsPtr = fileContents.c_str(); //array of strings*/



	//glShaderSource(id, 1, &contentsPtt, nullptr); //0
	glShaderSource(id, 1, &source, nullptr);

	glCompileShader(id);


	// // // // sve s wiki
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &errorLog[0]);
		std::cout << "Shader " + name + " failed to compile" <<std::endl;

	}
	std::cout << "JA SAM aaaaaa" << std::endl;
	// // // // sve s wiki


}


void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	//odnosti se na onaj prvi dio tih fieova in vec2
}
void GLSLProgram::linkShaders() {

	std::cout << "4.0" << std::endl;

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
		std::cout << errorLog[0] << std::endl;
		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		std::cout << "Shader failed to link" << std::endl;
		return;
	}
	// Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
}




void GLSLProgram::use() {
	glUseProgram(_programID);

	/*for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}*/

}
void GLSLProgram::unuse() {
	glUseProgram(0);

	/*glUseProgram(_programID);
	for (int i = 0; i <= _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
	glUseProgram(0);*/
}

GLint GLSLProgram::getUniformLocation(const std::string uniformName) {
	//dijeljena memorija u GPU koja je svima vidljiva
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
//		std::cout << "Uniform " + uniformName + " not found in shader" << std::endl;
		std::cout << "Uniform " + uniformName + " is not active in shader." << std::endl;
		//int i; std::cin >> i;
		//exit(69);
	}
	return location;

}
void GLSLProgram::dispose() {
	glUseProgram(0);
	if (_programID) 
		glDeleteProgram(_programID);
	// kad ovo pozoves u maingame destruktoru mozda javi gresku
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

}