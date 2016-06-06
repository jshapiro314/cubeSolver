#ifdef IML_WIN

#include <iml_loader.h>
#include <FreeImage.h>
#include <iml_log.h>
#include <fstream>


bool FileLoader::ReadTexture(const char *filename, TexData& out) {
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
    {
        //dib = FreeImage_Load(fif, filename.c_str());
        FIBITMAP *test = FreeImage_Load(fif, filename);
        dib = FreeImage_ConvertTo32Bits(test);
    }

    //if the image failed to load, return failure
    if (!dib)
        return false;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);

    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        return false;


    out.SetData(width * height, bits, width, height, GL_BGRA);
    //Texture* texture = Texture::Create2D(level, internalFormat, width, height, border, format, GL_UNSIGNED_BYTE, bits);

    //Free FreeImage's copy of the data
    FreeImage_Unload(dib);

    return true;
}


bool FileLoader::ReadTxtFile(const std::string &path, std::string &dest){
    std::ifstream in(path, std::ios::in | std::ios::binary);

    std::string msg = "Failed to open file " + path;
    ASSERT(in.is_open() && in.good(), msg.c_str());

    in.seekg(0, std::ios::end);         // Set get position to end
    dest.resize(in.tellg());            // Resize string to support enough bytes
    in.seekg(0, std::ios::beg);         // Set get position to beginning
    in.read(&dest[0], dest.size());     // Read file to string
    in.close();

    return true;
}

#endif
