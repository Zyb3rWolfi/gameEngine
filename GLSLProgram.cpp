//
// Created by Zyb3rWolfi on 08/01/2024.
//

#include "GLSLProgram.h"
#include<fstream>
#include<vector>
#include<glew.h>
#include<iostream>

GLSLProgram::GLSLProgram() : _programID(0), _fragmentShaderID(0), _vertexShaderID(0), _numAtrs(0) {
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
}

GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath) {
    // Creates an empty program object which the shader object can be attached to.
    _programID = glCreateProgram();
    // Creating a shader object for both the vertex and fragment
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Runs a function to compile the both shaders
    compileShader(vertexShaderFilePath, _vertexShaderID);
    compileShader(fragmentShaderFilePath, _fragmentShaderID);


}

void GLSLProgram::linkShaders() {

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.

// Attach our shaders to our program
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

// Link our program
    glLinkProgram(_programID);

// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(_programID);
        // Don't leak shaders either.
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);

        // Use the infoLog as you see fit.
        std::cout << "Error linking";
        // In this simple program, we'll just leave
        return;
    }

// Always detach shaders after a successful link.
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);

    std::cout << "SHADERS LINKED " << "\n";

}



// This manages compiling each shader file. We pass in the filepath to open the file and the ID of the shader.
void GLSLProgram::compileShader(const std::string &filePath, GLuint id) {

    // Opening the shader file
    std::ifstream vertexFile(filePath);

    // If the shader file cannot open we throw an error
    if (!vertexFile.is_open()) {
        std::cerr << "Unable to open " << filePath << "\n";
    }

    std::string fileContents;
    std::string line;

    // We read the file content and put the whole file into one string
    while (std::getline(vertexFile, line)) {
        fileContents += line + "\n";
    }

    vertexFile.close();

    // Creates a pointer to the file content which we convert to a single string
    const char* contentsPtr = fileContents.c_str();

    //Replaces the source code in a shader object
    glShaderSource(id, 1, &contentsPtr, nullptr);
    // Compiles the shader object
    glCompileShader(id);

    // Error detection
    GLint compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

    if(compiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(id);

        // Use the infoLog as you see fit.
        std::cerr << " Error COMPILING SHADERS " << &infoLog[0] << "\n";
        // In this simple program, we'll just leave
        return;
    }

    std::cout << "SHADER COMPILED " << compiled << "\n";
}

void GLSLProgram::addAttribute(const std::string &atrName) {

    glBindAttribLocation(_programID, _numAtrs++, atrName.c_str());

}

GLuint GLSLProgram::getUniformLocation(const std::string &uniformName) {

    GLuint location = glGetUniformLocation(_programID, uniformName.c_str());

    if (location == GL_INVALID_INDEX) {
        std::cerr << "Uniform not found in shader";
    }
    return location;
}

void GLSLProgram::use() {
    glUseProgram(_programID);
    for (int i = 0; i < _numAtrs; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < _numAtrs; i++) {
        glDisableVertexAttribArray(i);
    }
}

