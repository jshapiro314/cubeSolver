#ifndef __BASIC_FILE_LOADER_H__
#define __BASIC_FILE_LOADER_H__

#include <string>

#include "basic_texdata.h"

class FileLoader
{
private:
	static FileLoader* mInstance;

	FileLoader();

	~FileLoader();

public:
	static FileLoader* GetInstance();

	void Release();

	void ReadTexture(const char* filename, TexData& out) const;

	std::string ReadTxtFile(const std::string& filename) const;
};


#endif //__BASIC_FILE_LOADER_H__


