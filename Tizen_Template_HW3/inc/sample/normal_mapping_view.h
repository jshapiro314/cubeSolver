#ifndef NORMAL_MAPPING_VIEW_H_
#define NORMAL_MAPPING_VIEW_H_

#include "sample_view.h"

class NormalMappingView : public SampleView
{
public:
	NormalMappingView(void* data) : SampleView(data)
	{
	}

	void OnInit() override;

	void OnStep() override;
};




#endif /* NORMAL_MAPPING_VIEW_H_ */
