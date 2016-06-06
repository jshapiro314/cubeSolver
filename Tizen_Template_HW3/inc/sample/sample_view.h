#ifndef __SAMPLE_VIEW_H__
#define __SAMPLE_VIEW_H__

#include "basic/basic_renderer.h"

class SampleView
{
public:
	Evas_Object* GetGLView() const;

protected:
	Evas_Object* mGLView;
	BasicRenderer* mViewRenderer;

public:
	explicit SampleView(void* data);

	virtual ~SampleView();

	void Release();

public:
	virtual void OnInit() = 0;

	virtual void OnStep();

	void OnWindowUpdate(int w, int h) const;

	void RebindVbo() const;

	void SetTouchPoint(float x, float y) const;

	void TouchOn() const;

	void TouchOff() const;

	void TogglePolygonMode() const;

	void ZoomIn(const float& vel) const;

	void ZoomOut(const float& vel) const;

	void MoveForward(const float& vel) const;

	void MoveBackward(const float& vel) const;

	void MoveRight(const float& vel) const;

	void MoveLeft(const float& vel) const;

	void MoveUp(const float& vel) const;

	void MoveDown(const float& vel) const;

	void RotateCamera(const float& dx, const float& dy) const;

	Evas_Object* CreateView(void* data) const;
};

inline Evas_Object* SampleView::GetGLView() const
{
	return mGLView;
}

inline void SampleView::OnWindowUpdate(int w, int h) const
{
	mViewRenderer->SetViewPort(w, h);
}

inline void SampleView::RebindVbo() const
{
	mViewRenderer->RebindVbo();
}

inline void SampleView::OnStep()
{
	mViewRenderer->RenderFrame();
}

inline void SampleView::SetTouchPoint(float x, float y) const
{
	mViewRenderer->SetTouchPoint(x, y);
}

inline void SampleView::TouchOn() const
{
	mViewRenderer->TouchOn();
	mViewRenderer->OffAutoRotate();
}

inline void SampleView::TouchOff() const
{
	mViewRenderer->OnAutoRotate();
	mViewRenderer->TouchOff();
}

inline void SampleView::TogglePolygonMode() const
{
	mViewRenderer->TogglePolygonMode();
}

inline void SampleView::ZoomIn(const float& vel) const
{
	mViewRenderer->GetCamera()->ZoomIn(vel);
}

inline void SampleView::ZoomOut(const float& vel) const
{
	mViewRenderer->GetCamera()->ZoomOut(vel);
}

inline void SampleView::MoveForward(const float& vel) const
{
	mViewRenderer->GetCamera()->MoveForward(vel);
}

inline void SampleView::MoveBackward(const float& vel) const
{
	mViewRenderer->GetCamera()->MoveBackward(vel);
}

inline void SampleView::MoveRight(const float& vel) const
{
	mViewRenderer->GetCamera()->MoveRight(vel);
}

inline void SampleView::MoveLeft(const float& vel) const
{
	mViewRenderer->GetCamera()->MoveLeft(vel);
}

inline void SampleView::MoveUp(const float& vel) const
{
	mViewRenderer->GetCamera()->MoveUp(vel);
}

inline void SampleView::MoveDown(const float& vel) const
{
	mViewRenderer->GetCamera()->MoveDown(vel);
}

inline void SampleView::RotateCamera(const float& dx, const float& dy) const
{
	mViewRenderer->GetCamera()->Rotate(dx, dy);
}


#endif //__SAMPLE_VIEW_H__


