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
	mViewRenderer->buffNum = 0;
	mViewRenderer->SetProgram(vs, fs);


	string teapot = FileLoader::GetInstance()->ReadTxtFile("obj3d/teapot");
	string cube = FileLoader::GetInstance()->ReadTxtFile("obj3d/cube");
	string smallCube1 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube1");
	string smallCube2 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube2");
	string smallCube3 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube3");
	string smallCube4 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube4");
	string smallCube5 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube5");
	string smallCube6 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube6");
	string smallCube7 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube7");
	string smallCube8 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube8");
	string smallCube9 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube9");
	string smallCube10 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube10");
	string smallCube11 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube11");
	string smallCube12 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube12");
	string smallCube13 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube13");
	string smallCube15 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube15");
	string smallCube16 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube16");
	string smallCube17 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube17");
	string smallCube18 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube18");
	string smallCube19 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube19");
	string smallCube20 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube20");
	string smallCube21 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube21");
	string smallCube22 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube22");
	string smallCube23 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube23");
	string smallCube24 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube24");
	string smallCube25 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube25");
	string smallCube26 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube26");
	string smallCube27 = FileLoader::GetInstance()->ReadTxtFile("obj3d/smallCube27");

	//TexData textJ;
	//FileLoader::GetInstance()->ReadTexture("tex/tex_c_brick.bmp", textJ);


	float scale = 0.5f;
	mViewRenderer->SetNewModel(cube, scale);
	//mViewRenderer->SetTexture(TEXDATA_GENERAL, &textJ);

	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 1;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube1, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 2;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube2, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 3;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube3, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 4;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube4, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 5;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube5, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 6;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube6, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 7;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube7, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 8;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube8, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 9;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube9, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 10;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube10, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 11;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube11, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 12;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube12, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 13;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube13, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 14;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube15, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 15;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube16, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 16;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube17, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 17;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube18, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 18;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube19, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 19;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube20, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 20;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube21, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 21;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube22, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 22;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube23, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 23;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube24, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 24;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube25, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 25;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube26, scale);
	mViewRenderer->Initialize();

	mViewRenderer->buffNum = 26;
	mViewRenderer->SetProgram(vs, fs);
	mViewRenderer->SetNewModel(smallCube27, scale);
	mViewRenderer->Initialize();




	//mViewRenderer->buffNum = 0;

	mViewRenderer->OffAutoRotate();

	mViewRenderer->GetCamera()->SetEye(25, 25, 25);
	mViewRenderer->GetCamera()->SetAt(0, 0, 0);
}
