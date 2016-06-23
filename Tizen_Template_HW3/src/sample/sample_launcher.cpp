#include "sample/sample_launcher.h"
#include "gles_sample.h"

#include "sample/coloring_view.h"
#include "sample/frag_lighting_view.h"
#include "sample/normal_mapping_view.h"

SampleLauncher* SampleLauncher::instance = NULL;

SampleLauncher::SampleLauncher() :
	curView(NULL),
	mParent(NULL)
{
}

SampleLauncher::~SampleLauncher()
{
	if (instance)
		delete instance;
}

SampleLauncher* SampleLauncher::GetInstance()
{
	if (!instance)
	{
		instance = new SampleLauncher();
	}
	return instance;
}

void SampleLauncher::Release()
{
	if (curView)
	{
		delete curView;
		curView = NULL;
	}

	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

Evas_Object* SampleLauncher::InitSampleView(void* data)
{
	appdata_s* ad = static_cast<appdata_s *>(data);
	int sampleNum = ad->cur_sample_num;

	mParent = ad->win;

	if (curView)
	{
		delete curView;
		curView = NULL;
	}

	switch (sampleNum)
	{
	case 0:
		break;
	case 1:
		curView = new ColoringView(ad);
		break;
//	case 2:
//		curView = new FragLightingView(ad);
//		break;
//	case 3:
//		curView = new NormalMappingView(ad);
//		break;
	default:
		break;
	}

	return curView->GetGLView();
}

