#include <fstream>

#include "basic/basic_texdata.h"
#include "basic/basic_utils.h"
#include "basic/basic_file_loader.h"

using namespace std;

TexData::TexData() :
	pixels(nullptr),
	width(0),
	height(0),
	format(0)
{
}

TexData::~TexData()
{
	LOGI("TexData die.\n");
	if (pixels) delete pixels;
}

void TexData::SetData(int size, const GLubyte* source,
                      unsigned int w, unsigned int h, int fm)
{
	LOGI("TexData set.\n");
	//if(pixels) delete pixels;
	int channels(4);
	//if (fm == GL_RGBA || fm == GL_BGRA )	 { channels = 4; }
	//if (fm == GL_RGB  || fm == GL_BGR  )	 { channels = 3; }
	pixels = new GLubyte[size * channels];
	memcpy(this->pixels, source, channels * size * sizeof(GLubyte));
	width = w;
	height = h;
	format = fm;
}

