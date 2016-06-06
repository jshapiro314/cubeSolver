#include "sample/coloring_view.h"

#include "basic/basic_file_loader.h"

using namespace std;

ColoringView::ColoringView(void* data): SampleView(data)
{
}

void ColoringView::OnInit()
{
	string vs = FileLoader::GetInstance()->ReadTxtFile("shader/view_color/color.vs");
	string fs = FileLoader::GetInstance()->ReadTxtFile("shader/view_color/color.fs");
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->buffNum = 0;

	string teapot = FileLoader::GetInstance()->ReadTxtFile("obj3d/teapot");
	string cube = FileLoader::GetInstance()->ReadTxtFile("obj3d/cube");
	string cube2 = FileLoader::GetInstance()->ReadTxtFile("obj3d/cube2");
	string cube3 = FileLoader::GetInstance()->ReadTxtFile("obj3d/cube3");

	//TexData textJ;
	//FileLoader::GetInstance()->ReadTexture("tex/tex_c_brick.bmp", textJ);


	float scale = 1.0f;
	mViewRenderer->SetNewModel(cube2, scale);
	//mViewRenderer->SetTexture(TEXDATA_GENERAL, &textJ);

	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 1;
	mViewRenderer->SetNewModel(cube3, scale);
	mViewRenderer->Initialize();

	//mViewRenderer->buffNum = 0;

	mViewRenderer->OffAutoRotate();

	mViewRenderer->GetCamera()->SetEye(25, 25, 25);
	mViewRenderer->GetCamera()->SetAt(0, 0, 0);
}
