#ifndef __BASIC_TEXDATA_H__
#define __BASIC_TEXDATA_H__

#include "basic_gl_set.h"


typedef enum
{
	TEXDATA_GENERAL, // general texture
	TEXDATA_NORMAL_MAP, // normal map texture
	TEXDATA_CUBE_MAP, // cube map texture
	TEXDATA_HEIGHT_MAP, // height map texture
	TEXDATA_MIPMAP // mipmap texture
} TexData_Type;


class TexData
{
public:
	GLubyte* pixels;
	GLuint width;
	GLuint height;
	GLint format;

	TexData();

	~TexData();

	void SetData(int size, const GLubyte* source,
	             unsigned int w, unsigned int h, int fm);
};


#endif //__BASIC_TEXDATA_H__


