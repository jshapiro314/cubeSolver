#ifndef __COLORING_VIEW_H__
#define __COLORING_VIEW_H__

#include "sample_view.h"

class ColoringView : public SampleView
{
public:
	explicit ColoringView(void* data);

	void OnInit() override;
};


#endif //__COLORING_VIEW_H__
