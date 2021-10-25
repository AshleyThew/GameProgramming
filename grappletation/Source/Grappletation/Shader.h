// COMP710 GP Framework 2021
#ifndef __SHADER_H__
#define __SHADER_H__
#include "GL\glew.h"
// Forward declarations:
struct Matrix4;
class Shader
{
	// Member methods:
public:
	Shader();
	~Shader();
	bool Load(const char* vertexFile, const char* pixelFile);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	void SetVector4Uniform(const char* name, float x, float y, float z, float w);
protected:
private:
	bool IsValidProgram();
	static bool CompileShader(const char* filename, GLenum shaderType, GLuint& outShader);
	static bool IsCompiled(GLuint shader);
	// Member data:
public:
protected:
	GLuint m_vertexShader;
	GLuint m_pixelShader;
	GLuint m_shaderProgram;
private:
};
#endif // __SHADER_H__