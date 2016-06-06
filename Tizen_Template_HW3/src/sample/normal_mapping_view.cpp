#include "sample/normal_mapping_view.h"

#include "basic/basic_file_loader.h"

using namespace std;

void NormalMappingView::OnInit()
{
	string vs = FileLoader::GetInstance()->ReadTxtFile("shader/view_nor/nor.vs");
	string fs = FileLoader::GetInstance()->ReadTxtFile("shader/view_nor/nor.fs");
	mViewRenderer->SetProgram(vs, fs);

	string teapot = FileLoader::GetInstance()->ReadTxtFile("obj3d/teapot");

	TexData tex, normal_tex;
	FileLoader::GetInstance()->ReadTexture("tex/tex_c_brick.bmp", tex);
	FileLoader::GetInstance()->ReadTexture("tex/tex_n_brick.bmp", normal_tex);

	float scale = 1.0f;
	mViewRenderer->SetNewModel(teapot, scale);
	mViewRenderer->SetTexture(TEXDATA_GENERAL, &tex);
	mViewRenderer->SetTexture(TEXDATA_NORMAL_MAP, &normal_tex);

	mViewRenderer->Initialize();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	mViewRenderer->GetCamera()->SetEye(25, 25, 25);
	mViewRenderer->GetCamera()->SetAt(0, 0, 0);
}

void NormalMappingView::OnStep()
{
	mViewRenderer->RenderFrame();
}

