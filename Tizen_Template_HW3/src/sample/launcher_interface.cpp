#include "sample/launcher_interface.h"

#include "sample/sample_launcher.h"


SampleLauncher* getLoader()
{
	return SampleLauncher::GetInstance();
}

Evas_Object*
get_sample_view(void* data)
{
	return getLoader()->InitSampleView(data);
}

void
release_loader()
{
	getLoader()->Release();
}

