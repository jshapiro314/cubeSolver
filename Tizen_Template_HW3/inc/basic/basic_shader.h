#ifndef __BASIC_SHADER_H__
#define __BASIC_SHADER_H__

#include <map>
#include "basic_gl_set.h"

class BasicShader
{
public:
	const int V_ATTRIB_POSITION = 0;
	const int V_ATTRIB_NORMAL = 1;
	const int V_ATTRIB_TEX = 2;
	const int V_ATTRIB_TANGENT = 3;

private:
	// glProgram object member
	GLuint mProgram;
	std::map<std::string, int> mUniformLocations;

public:
	BasicShader();

	~BasicShader();

	bool Use() const;

	GLuint LoadShader(GLenum shaderType, const char* source) const;

	GLuint LinkShaders(int nArgs, ...) const;

	GLuint CreateProgram(const std::string& vertexSource, const std::string& fragmentSource);

	GLuint CreateProgram(const char* vertexSource, const char* fragmentSource);

	GLuint CreateTesselProgram(const char* vertexSource,
	                           const char* tessControlSource,
	                           const char* tessEvalSource,
	                           const char* geometrySource,
	                           const char* fragmentSource) const;


	void SetUniform(const char* name, const float& x, const float& y, const float& z);

	void SetUniform(const char* name, const glm::vec3& v);

	void SetUniform(const char* name, const glm::vec2& v);

	void SetUniform(const char* name, const glm::mat4& m);

	void SetUniform(const char* name, const glm::mat3& m);

	void SetUniform(const char* name, const glm::vec4& v);

	void SetUniform(const char* name, const float& val);

	void SetUniform(const char* name, const int& val);

	void SetUniform(const char* name, const GLuint& val);

	void SetUniform(const char* name, const bool& val);

	const GLuint GetProgram() const;

private:

	int GetUniformLocation(const char* name);
};

inline const GLuint BasicShader::GetProgram() const
{
	return mProgram;
}

#endif //__BASIC_SHADER_H__


