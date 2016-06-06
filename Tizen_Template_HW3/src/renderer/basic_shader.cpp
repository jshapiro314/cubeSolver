#include <iostream>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdarg.h>

#include "basic/basic_shader.h"
#include "basic/basic_utils.h"

using namespace std;
using namespace glm;

BasicShader::BasicShader() :
	mProgram(0)
{
}

BasicShader::~BasicShader()
{
	if (mProgram > 0) glDeleteProgram(mProgram);
}


bool BasicShader::Use() const
{
	glUseProgram(mProgram);
	check_gl_error("glUseProgram");

	return true;
}

GLuint BasicShader::LoadShader(GLenum shaderType, const char* source) const
{
	GLuint shader = glCreateShader(shaderType);

	if (shader)
	{
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen)
			{
				char* buf = static_cast<char *>(malloc(infoLen));

				if (buf)
				{
					glGetShaderInfoLog(shader, infoLen, nullptr, buf);
					LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
					free(buf);
				}

				glDeleteShader(shader);
			}
			exit(1);
		}
	}
	return shader;
}

GLuint BasicShader::LinkShaders(int nArgs, ...) const
{
	GLuint program = glCreateProgram();
	if (program)
	{
		va_list ap;
		va_start(ap, nArgs);

		for (int i = 1; i <= nArgs; ++i)
		{
			glAttachShader(program, va_arg(ap, GLint));
			check_gl_error("glAttachShader");
		}

		glBindAttribLocation(program, V_ATTRIB_POSITION, "position");
		glBindAttribLocation(program, V_ATTRIB_NORMAL, "normal");
		glBindAttribLocation(program, V_ATTRIB_TEX, "texCoord");
		glBindAttribLocation(program, V_ATTRIB_TANGENT, "tangent");
		check_gl_error("glBindAttribLocation");

		glLinkProgram(program);
		check_gl_error("glLinkProgram");

		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE)
		{
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength)
			{
				char* buf = static_cast<char *>(malloc(bufLength));
				if (buf)
				{
					glGetProgramInfoLog(program, bufLength, nullptr, buf);
					LOGE("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			exit(1);
		}
	}

	return program;
}

GLuint BasicShader::CreateProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
	return CreateProgram(vertexSource.c_str(), fragmentSource.c_str());
}

GLuint BasicShader::CreateProgram(const char* vertexSource, const char* fragmentSource)
{
	GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentSource);


	if (!vertexShader || !fragmentShader) return 0;

	mProgram = LinkShaders(2, vertexShader, fragmentShader);
	return mProgram;
}

int BasicShader::GetUniformLocation(const char* name)
{
	map<string, int>::iterator pos;
	pos = mUniformLocations.find(name);

	if (pos == mUniformLocations.end())
	{
		mUniformLocations[name] = glGetUniformLocation(mProgram, name);
	}

	return mUniformLocations[name];
}


void BasicShader::SetUniform(const char* name, const float& x, const float& y, const float& z)
{
	GLint loc = GetUniformLocation(name);
	glUniform3f(loc, x, y, z);
	check_gl_error("glUniform3f");
}

void BasicShader::SetUniform(const char* name, const vec3& v)
{
	this->SetUniform(name, v.x, v.y, v.z);
}

void BasicShader::SetUniform(const char* name, const vec4& v)
{
	GLint loc = GetUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
	check_gl_error("glUniform4f");
}

void BasicShader::SetUniform(const char* name, const vec2& v)
{
	GLint loc = GetUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
	check_gl_error("glUniform2f");
}

void BasicShader::SetUniform(const char* name, const mat4& m)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(m));
	check_gl_error("glUniformMatrix4fv");
}

void BasicShader::SetUniform(const char* name, const mat3& m)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(m));
	check_gl_error("glUniformMatrix3fv");
}

void BasicShader::SetUniform(const char* name, const float& val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1f(loc, val);
	check_gl_error("glUniform1f");
}

void BasicShader::SetUniform(const char* name, const int& val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1i(loc, val);
	check_gl_error("glUniform1i");
}

void BasicShader::SetUniform(const char* name, const GLuint& val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1i(loc, val);
	check_gl_error("glUniform3f");
}

void BasicShader::SetUniform(const char* name, const bool& val)
{
	int loc = GetUniformLocation(name);
	glUniform1i(loc, val);
	check_gl_error("glUniform1i");
}

