#include "basic/basic_utils.h"

char* util_strtok(char* str, const char* delim, char** nextp)
{
	char* ret;

	if (str == nullptr)
	{
		str = *nextp;
	}

	str += strspn(str, delim);

	if (*str == '\0')
	{
		return nullptr;
	}

	ret = str;

	str += strcspn(str, delim);

	if (*str)
	{
		*str++ = '\0';
	}

	*nextp = str;

	return ret;
}

void print_gl_string(const char* name, GLenum s)
{
	const char* v = reinterpret_cast<const char *>(glGetString(s));
	LOGI("GL %s = %s\n", name, v);
}

void check_gl_error(const char* op)
{
	for (GLint error = glGetError(); error; error
	     = glGetError())
	{
		LOGE("after %s() glError (0x%x)\n", op, error);
	}
}

void log_string(const char* source)
{
	char *temp, *tempPtr;

	temp = new char[2048];
	strcpy(temp, source);

	util_strtok(temp, "\n\r", &tempPtr);
	while (temp)
	{
		LOGI("%s", temp);
		temp = util_strtok(nullptr, "\n\r", &tempPtr);
	}

	delete temp;
}

