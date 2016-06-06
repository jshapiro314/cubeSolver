#ifndef __LOADER_INTERFACE_H__
#define __LOADER_INTERFACE_H__

#include <Elementary.h>

#ifdef __cplusplus
extern "C"
{
#endif

	Evas_Object* get_sample_view(void* data);

	void release_loader();

#ifdef __cplusplus
}
#endif

#endif //__LOADER_INTERFACE_H__


