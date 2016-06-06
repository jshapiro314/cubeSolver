#include "basic/basic_file_loader.h"

FileLoader *FileLoader::mInstance = NULL;

FileLoader::FileLoader() {

}

FileLoader::~FileLoader() {

}

FileLoader *FileLoader::GetInstance() {
    if (!mInstance) {
        mInstance = new FileLoader();
    }
    return mInstance;
}


void FileLoader::Release() {
    if (mInstance) {
        delete mInstance;
        mInstance = NULL;

    }
}
