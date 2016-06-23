#include "sample/frag_lighting_view.h"

#include "basic/basic_file_loader.h"

using namespace std;

void FragLightingView::OnInit()
{
	string vs = FileLoader::GetInstance()->ReadTxtFile("shader/view_f_lit/f_lit.vs");
	string fs = FileLoader::GetInstance()->ReadTxtFile("shader/view_f_lit/f_lit.fs");
	mViewRenderer->buffNum = 0;
	mViewRenderer->SetProgram(vs, fs);

	string teapot = FileLoader::GetInstance()->ReadTxtFile("obj3d/cube");

	TexData textJ;
	FileLoader::GetInstance()->ReadTexture("i3dp_0807.png", textJ);

	float scale = 1.0f;
	mViewRenderer->SetNewModel(teapot, scale);
	mViewRenderer->SetTexture(TEXDATA_GENERAL, &textJ);

	mViewRenderer->Initialize();
	glClearColor(0.1f, 0.1f, 0.3f, 0.0f);

	mViewRenderer->GetCamera()->SetEye(25, 25, 25);
	mViewRenderer->GetCamera()->SetAt(0, 0, 0);
}

void FragLightingView::OnStep()
{
	mViewRenderer->RenderFrame();
}

