#ifndef __FRAG_LIGHTING_VIEW_H__
#define __FRAG_LIGHTING_VIEW_H__

#include "sample_view.h"

class FragLightingView : public SampleView
{
public:
	FragLightingView(void* data) : SampleView(data)
	{
	}

	void OnInit() override;

	void OnStep() override;
};


#endif //__FRAG_LIGHTING_VIEW_H__


