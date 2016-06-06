#ifndef __BASIC_GL_SET_H__
#define __BASIC_GL_SET_H__

#ifdef BASIC_ANDROID
#include <android/log.h>
#include <GLES3/gl31.h>
#endif

#ifdef BASIC_WIN
#include <gl/glew.h>
#endif

#ifdef BASIC_TIZEN

#include <Elementary_GL_Helpers.h>

ELEMENTARY_GLVIEW_GLOBAL_DECLARE()
#endif

#endif //__BASIC_GL_SET_H__


