#ifndef __SAMPLE_LAUNCHER_H__
#define __SAMPLE_LAUNCHER_H__

#include "sample_view.h"

class SampleLauncher
{
private:
	static SampleLauncher* instance;

	SampleView* curView;

private:
	Evas_Object* mParent;

	SampleLauncher();

	~SampleLauncher();


public:
	static SampleLauncher* GetInstance();

	Evas_Object* InitSampleView(void* data);

	Evas_Object* GetParent() const;

	void Release();
};

inline Evas_Object* SampleLauncher::GetParent() const
{
	return mParent;
}

#endif //__SAMPLE_LAUNCHER_H__


