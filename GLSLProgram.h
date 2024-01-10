//
// Created by Zyb3rWolfi on 08/01/2024.
//

#ifndef UNTITLED_GLSLPROGRAM_H
#define UNTITLED_GLSLPROGRAM_H
#include<string>
#include<glew.h>

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    void addAttribute(const std::string& atrName);
    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void linkShaders();

    GLuint getUniformLocation(const std::string& uniformName);

    void use();
    void unuse();
private:
    int _numAtrs;
    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
    void compileShader(const std::string& filePath, GLuint id);

};


#endif //UNTITLED_GLSLPROGRAM_H
