#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "basic/basic_renderer.h"

using namespace std;
using namespace glm;

BasicRenderer::BasicRenderer() :
	mWidth(0),
	mHeight(0),
	mDeltaTime(0),
	mTimer(NULL),
	mCamera(NULL),
	//mShader(NULL),
	mIsAutoRotateEye(true),
	mIsFill(true),
	mIsTouchOn(false),
	mTouchPoint(glm::vec2(0)),
	mHasTexture(false),
	mHasCubemap(false),
	mHasNorMap(false),
	mHasHeightmap(false),
	mTexId(0),
	mTexCubeId(0),
	mTexNorId(0),
	mTexHeightId(0),
	mInstCount(1)
{
	mTimer = new BasicTimer();
	mCamera = new BasicCamera();
	//mShader = new BasicShader();
}

BasicRenderer::~BasicRenderer()
{
	delete mTimer;
	//delete mShader;
	delete mCamera;
}

// Interface functions
/// Sets vertex shader and fragment shader for rendering
bool BasicRenderer::SetProgram(const std::string& vertexSource, const std::string& fragmentSource) const
{
	//vertexBuffer[buffNum].mShader = new BasicShader();
	vertexBuffer[buffNum].mShader->CreateProgram(vertexSource, fragmentSource);

	if (!vertexBuffer[buffNum].mShader->GetProgram())
	{
		LOGE("Could not create program.\n");
		return false;
	}

	vertexBuffer[buffNum].mShader->Use();

	return true;
}

bool BasicRenderer::SetProgram(const char* vertexSource, const char* fragmentSource) const
{
	vertexBuffer[buffNum].mShader->CreateProgram(vertexSource, fragmentSource);

	if (!vertexBuffer[buffNum].mShader->GetProgram())
	{
		LOGE("Could not create program.\n");
		return false;
	}

	vertexBuffer[buffNum].mShader->Use();

	return true;
}

/****************************
 **** Interface functions ***
 ****************************/
void BasicRenderer::SetNewModel(const std::string& objSource, const float& scale)
{
	char* buffer = new char[objSource.length() + 1];
	strcpy(buffer, objSource.c_str());

	SetNewModel(buffer, scale);

	delete (buffer);
}

void BasicRenderer::SetNewModel(char* objSource)
{
	ImportModel(objSource, this);
}

void BasicRenderer::SetNewModel(char* objSource, const float& scale)
{
	ImportModelScale(objSource, this, scale);
	mHasTexture = true;
}

void BasicRenderer::SetTexture(TexData_Type type, const TexData* newTex)
{
	switch (type)
	{
	case TEXDATA_GENERAL: // general texture
		LOGI("Set Texture : general\n");
		mHasTexture = true;
		CreateTexBuffer(*newTex, mTexId);
		break;
	case TEXDATA_NORMAL_MAP: // normal map
		LOGI("Set Texture : normal map\n");
		mHasNorMap = true;
		if (vertexBuffer[buffNum].mTangentBuffer.empty()) ComputeTangent();
		CreateTexBuffer(*newTex, mTexNorId);
		break;
	default:
		break;
	}
}

bool BasicRenderer::Initialize()
{
	LOGI("Initialize renderer.\n");
	LogInfo();

	CountTickInit();

	CreateVbo();
	SetState();

	return true;
}

void BasicRenderer::SetViewPort(int w, int h)
{
	LOGI("SetViewPort(%d, %d)\n", w, h);
	mWidth = w;
	mHeight = h;
	glViewport(0, 0, w, h);
	check_gl_error("glViewport");

	mCamera->ComputePerspective(60.0f, w, h);
}

void BasicRenderer::RenderFrame()
{
	static float timeCount = 0;

	//LOGI("BasicRenderer::RenderFrame()");
	ComputeTick();
	//mat4 worldMatRot = GetWorldMatrix();

	if (mIsAutoRotateEye) mCamera->RotateAuto(mDeltaTime);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	check_gl_error("glClear");

	double timeElapsed = mTimer->GetElapsedTime();

	static int count = 0;
	float theta = -0.01745;
	float Ntheta =0.01745;
	mat4 rotateX = mat4(1,0,0,0,0,cos(theta),sin(theta),0,0,sin(theta)*-1,cos(theta),0,0,0,0,1);
	mat4 rotateY = mat4(cos(theta), 0, sin(theta)*-1, 0, 0, 1, 0, 0, sin(theta), 0, cos(theta), 0, 0, 0, 0, 1 );
	mat4 rotateZ = mat4(cos(theta), sin(theta), 0, 0, sin(theta)*-1, cos(theta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 );
	mat4 NrotateX = mat4(1,0,0,0,0,cos(Ntheta),sin(Ntheta),0,0,sin(Ntheta)*-1,cos(Ntheta),0,0,0,0,1);
	mat4 NrotateY = mat4(cos(Ntheta), 0, sin(Ntheta)*-1, 0, 0, 1, 0, 0, sin(Ntheta), 0, cos(Ntheta), 0, 0, 0, 0, 1 );
	mat4 NrotateZ = mat4(cos(Ntheta), sin(Ntheta), 0, 0, sin(Ntheta)*-1, cos(Ntheta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 );

	//rotate F
	if(timeElapsed > 2 && count < 90){

		for(int i=1;i<10;i++){
			vertexBuffer[i].worldMat = vertexBuffer[i].worldMat * rotateZ;
		}
		count++;
	}

	//rotate R
	if(count < 180 && count > 89){

		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * rotateY;
		vertexBuffer[2].worldMat = vertexBuffer[2].worldMat * rotateY;
		vertexBuffer[3].worldMat = vertexBuffer[3].worldMat * rotateY;
		vertexBuffer[12].worldMat = vertexBuffer[12].worldMat * rotateX;
		vertexBuffer[14].worldMat = vertexBuffer[14].worldMat * rotateX;
		vertexBuffer[17].worldMat = vertexBuffer[17].worldMat * rotateX;
		vertexBuffer[20].worldMat = vertexBuffer[20].worldMat * rotateX;
		vertexBuffer[23].worldMat = vertexBuffer[23].worldMat * rotateX;
		vertexBuffer[26].worldMat = vertexBuffer[26].worldMat * rotateX;

		count++;
	}

	//rotate B
	if(count < 270 && count > 179){

		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * NrotateX;
		vertexBuffer[12].worldMat = vertexBuffer[12].worldMat * rotateY;
		vertexBuffer[20].worldMat = vertexBuffer[20].worldMat * rotateY;
		vertexBuffer[19].worldMat = vertexBuffer[19].worldMat * NrotateZ;
		vertexBuffer[22].worldMat = vertexBuffer[22].worldMat * NrotateZ;
		vertexBuffer[25].worldMat = vertexBuffer[25].worldMat * NrotateZ;
		vertexBuffer[18].worldMat = vertexBuffer[18].worldMat * NrotateZ;
		vertexBuffer[21].worldMat = vertexBuffer[21].worldMat * NrotateZ;
		vertexBuffer[24].worldMat = vertexBuffer[24].worldMat * NrotateZ;

		count++;
	}

	//rotate L
	if(count < 360 && count > 269){

		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * rotateZ;
		vertexBuffer[19].worldMat = vertexBuffer[19].worldMat * rotateY;
		vertexBuffer[18].worldMat = vertexBuffer[18].worldMat * rotateY;
		vertexBuffer[10].worldMat = vertexBuffer[10].worldMat * NrotateX;
		vertexBuffer[13].worldMat = vertexBuffer[13].worldMat * NrotateX;
		vertexBuffer[15].worldMat = vertexBuffer[15].worldMat * NrotateX;
		vertexBuffer[7].worldMat = vertexBuffer[7].worldMat * NrotateY;
		vertexBuffer[8].worldMat = vertexBuffer[8].worldMat * NrotateY;
		vertexBuffer[9].worldMat = vertexBuffer[9].worldMat * NrotateY;

		count++;
	}

	//rotate T
	if(count < 450 && count > 359){

		vertexBuffer[18].worldMat = vertexBuffer[18].worldMat * NrotateZ;
		vertexBuffer[19].worldMat = vertexBuffer[19].worldMat * NrotateZ;
		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * NrotateX;
		vertexBuffer[12].worldMat = vertexBuffer[12].worldMat * rotateX;
		vertexBuffer[11].worldMat = vertexBuffer[11].worldMat * rotateY;
		vertexBuffer[4].worldMat = vertexBuffer[4].worldMat * NrotateX;
		vertexBuffer[20].worldMat = vertexBuffer[20].worldMat * rotateX;
		vertexBuffer[2].worldMat = vertexBuffer[2].worldMat * rotateZ;
		vertexBuffer[3].worldMat = vertexBuffer[3].worldMat * rotateZ;

		count++;
	}

	//rotate U
	if(count < 540 && count > 449){

		vertexBuffer[7].worldMat = vertexBuffer[7].worldMat * rotateZ;
		vertexBuffer[8].worldMat = vertexBuffer[8].worldMat * rotateZ;
		vertexBuffer[9].worldMat = vertexBuffer[9].worldMat * rotateZ;
		vertexBuffer[6].worldMat = vertexBuffer[6].worldMat * rotateX;
		vertexBuffer[16].worldMat = vertexBuffer[16].worldMat * NrotateY;
		vertexBuffer[21].worldMat = vertexBuffer[21].worldMat * NrotateX;
		vertexBuffer[26].worldMat = vertexBuffer[26].worldMat * NrotateZ;
		vertexBuffer[23].worldMat = vertexBuffer[23].worldMat * NrotateZ;
		vertexBuffer[24].worldMat = vertexBuffer[24].worldMat * NrotateX;

		count++;
	}

	//rotate Ui
	if(count < 630 && count > 539){

		vertexBuffer[7].worldMat = vertexBuffer[7].worldMat * NrotateZ;
		vertexBuffer[8].worldMat = vertexBuffer[8].worldMat * NrotateZ;
		vertexBuffer[9].worldMat = vertexBuffer[9].worldMat * NrotateZ;
		vertexBuffer[6].worldMat = vertexBuffer[6].worldMat * NrotateX;
		vertexBuffer[16].worldMat = vertexBuffer[16].worldMat * rotateY;
		vertexBuffer[21].worldMat = vertexBuffer[21].worldMat * rotateX;
		vertexBuffer[26].worldMat = vertexBuffer[26].worldMat * rotateZ;
		vertexBuffer[23].worldMat = vertexBuffer[23].worldMat * rotateZ;
		vertexBuffer[24].worldMat = vertexBuffer[24].worldMat * rotateX;

		count++;
	}

	//rotate Ti
	if(count < 720 && count > 629){

		vertexBuffer[18].worldMat = vertexBuffer[18].worldMat * rotateZ;
		vertexBuffer[19].worldMat = vertexBuffer[19].worldMat * rotateZ;
		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * rotateX;
		vertexBuffer[12].worldMat = vertexBuffer[12].worldMat * NrotateX;
		vertexBuffer[11].worldMat = vertexBuffer[11].worldMat * NrotateY;
		vertexBuffer[4].worldMat = vertexBuffer[4].worldMat * rotateX;
		vertexBuffer[20].worldMat = vertexBuffer[20].worldMat * NrotateX;
		vertexBuffer[2].worldMat = vertexBuffer[2].worldMat * NrotateZ;
		vertexBuffer[3].worldMat = vertexBuffer[3].worldMat * NrotateZ;

		count++;
	}

	//rotate Li
	if(count < 810 && count > 719){

		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * NrotateZ;
		vertexBuffer[19].worldMat = vertexBuffer[19].worldMat * NrotateY;
		vertexBuffer[18].worldMat = vertexBuffer[18].worldMat * NrotateY;
		vertexBuffer[10].worldMat = vertexBuffer[10].worldMat * rotateX;
		vertexBuffer[13].worldMat = vertexBuffer[13].worldMat * rotateX;
		vertexBuffer[15].worldMat = vertexBuffer[15].worldMat * rotateX;
		vertexBuffer[7].worldMat = vertexBuffer[7].worldMat * rotateY;
		vertexBuffer[8].worldMat = vertexBuffer[8].worldMat * rotateY;
		vertexBuffer[9].worldMat = vertexBuffer[9].worldMat * rotateY;

		count++;
	}

	//rotate Bi
	if(count < 900 && count > 809){

		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * rotateX;
		vertexBuffer[12].worldMat = vertexBuffer[12].worldMat * NrotateY;
		vertexBuffer[20].worldMat = vertexBuffer[20].worldMat * NrotateY;
		vertexBuffer[19].worldMat = vertexBuffer[19].worldMat * rotateZ;
		vertexBuffer[22].worldMat = vertexBuffer[22].worldMat * rotateZ;
		vertexBuffer[25].worldMat = vertexBuffer[25].worldMat * rotateZ;
		vertexBuffer[18].worldMat = vertexBuffer[18].worldMat * rotateZ;
		vertexBuffer[21].worldMat = vertexBuffer[21].worldMat * rotateZ;
		vertexBuffer[24].worldMat = vertexBuffer[24].worldMat * rotateZ;

		count++;
	}

	//rotate Ri
	if(count < 990 && count > 899){

		vertexBuffer[1].worldMat = vertexBuffer[1].worldMat * NrotateY;
		vertexBuffer[2].worldMat = vertexBuffer[2].worldMat * NrotateY;
		vertexBuffer[3].worldMat = vertexBuffer[3].worldMat * NrotateY;
		vertexBuffer[12].worldMat = vertexBuffer[12].worldMat * NrotateX;
		vertexBuffer[14].worldMat = vertexBuffer[14].worldMat * NrotateX;
		vertexBuffer[17].worldMat = vertexBuffer[17].worldMat * NrotateX;
		vertexBuffer[20].worldMat = vertexBuffer[20].worldMat * NrotateX;
		vertexBuffer[23].worldMat = vertexBuffer[23].worldMat * NrotateX;
		vertexBuffer[26].worldMat = vertexBuffer[26].worldMat * NrotateX;

		count++;
	}

	//rotate Fi
	if(count < 1080 && count > 989){

		for(int i=1;i<10;i++){
			vertexBuffer[i].worldMat = vertexBuffer[i].worldMat * NrotateZ;
		}
		count++;
	}

	if(count == 1080){
		count = 0;
	}


//	if(mTimer->GetElapsedTime() > 5 && mTimer->GetElapsedTime() < 10){
//		mat4 translate = mat4(1,0,0,0,0,1,0,0,0,0,1,0,5,0,0,1);
//		worldMat = GetWorldMatrix() * translate;
//	}

	for(int i=0;i<27;i++){
		vertexBuffer[i].mShader->Use();
		PassUniform(i);
		Draw(i);
	}


}

void BasicRenderer::TogglePolygonMode()
{
#ifdef BASIC_OPENGL
    mIsFill = !mIsFill;
    glPolygonMode(GL_FRONT_AND_BACK, mIsFill ? GL_FILL : GL_LINE);
#endif
}


/*****************************
 ***** Texture functions *****
 *****************************/
void BasicRenderer::CreateTexBuffer(const TexData& newTex, GLuint& target) const
{
	LOGI("BasicRenderer::CreateTexBuffer\n");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	check_gl_error("glPixelStorei");
	glGenTextures(1, &target);
	check_gl_error("glGenTextures");

	glBindTexture(GL_TEXTURE_2D, target);
	check_gl_error("glBindTexture");

	TexBuffer(GL_TEXTURE_2D, newTex);

	glGenerateMipmap(GL_TEXTURE_2D);
	check_gl_error("glGenerateMipmap");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	check_gl_error("glTexParameteri");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	check_gl_error("glTexParameteri");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	check_gl_error("glTexParameteri");

	glBindTexture(GL_TEXTURE_2D, 0);
}

void BasicRenderer::TexBuffer(GLenum type, const TexData& newTex) const
{
	LOGI("BasicRenderer::TexBuffer");

	glTexImage2D(type, 0, newTex.format,
	             newTex.width, newTex.height, 0,
	             static_cast<GLenum>(newTex.format), GL_UNSIGNED_BYTE,
	             static_cast<void *>(newTex.pixels));

	check_gl_error("glTexImage2D");
}


/*******************************
 ***** Rendering functions *****
 *******************************/
void BasicRenderer::SetState() const
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}

void BasicRenderer::CreateVbo()
{
	LOGI("BasicRenderer::RebindVbo\n");
	glGenBuffers(1, &vertexBuffer[buffNum].mVboVertices);
	glGenBuffers(1, &vertexBuffer[buffNum].mVboIndices);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[buffNum].mVboVertices);
	glBufferData(GL_ARRAY_BUFFER,
	                            static_cast<GLsizeiptr>(vertexBuffer[buffNum].mVertexBuffer.size() * sizeof(VertexStruct)),
	                            &(vertexBuffer[buffNum].mVertexBuffer.at(0)), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[buffNum].mVboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	                                    static_cast<GLsizeiptr>(vertexBuffer[buffNum].mIndexBuffer.size() * sizeof(GLushort)),
	                                    &(vertexBuffer[buffNum].mIndexBuffer.at(0)), GL_STATIC_DRAW);


	int stride = sizeof(VertexStruct); // stride: sizeof(float) * number of components
	int offset = 0;
	glEnableVertexAttribArray(V_ATTRIB_POSITION);
	glVertexAttribPointer(V_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

	offset += sizeof(vec3);
	glEnableVertexAttribArray(V_ATTRIB_NORMAL);
	glVertexAttribPointer(V_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

	// If renderer has texture, we should enable vertex attribute for texCoord
	if (mHasTexture || mHasNorMap)
	{
		offset += sizeof(vec3);
		glEnableVertexAttribArray(V_ATTRIB_TEX);
		glVertexAttribPointer(V_ATTRIB_TEX, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexId);
	}

	if (mHasNorMap)
	{
		// Bump mapping need to change space (world and TBN)
		// mTangentBuffer calculated by ComputeTangent() when normal texture has set
		glGenBuffers(1, &vertexBuffer[buffNum].mVboTangents);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[buffNum].mVboTangents);
		glBufferData(GL_ARRAY_BUFFER,
		                            static_cast<GLsizeiptr>(vertexBuffer[buffNum].mTangentBuffer.size() * sizeof(vec3)), &(vertexBuffer[buffNum].mTangentBuffer.at(0)), GL_STATIC_DRAW);

		offset = 0;
		stride = sizeof(vec3);
		glEnableVertexAttribArray(V_ATTRIB_TANGENT);
		glVertexAttribPointer(V_ATTRIB_TANGENT, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

		glActiveTexture(GL_TEXTURE0 + TEX_POS_NORMAL);
		glBindTexture(GL_TEXTURE_2D, mTexNorId);
	}
}

void BasicRenderer::RebindVbo() const
{
	//for(int i=0; i<=buffNum; i++){
	int i=0;
	LOGI("BasicRenderer::RebindVbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i].mVboVertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[i].mVboIndices);

	int stride = sizeof(VertexStruct); // stride: sizeof(float) * number of components
	int offset = 0;
	glEnableVertexAttribArray(V_ATTRIB_POSITION);
	glVertexAttribPointer(V_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

	offset += sizeof(vec3);
	glEnableVertexAttribArray(V_ATTRIB_NORMAL);
	glVertexAttribPointer(V_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

	// If renderer has texture, we should enable vertex attribute for texCoord
	if (mHasTexture || mHasNorMap)
	{
		offset += sizeof(vec3);
		glEnableVertexAttribArray(V_ATTRIB_TEX);
		glVertexAttribPointer(V_ATTRIB_TEX, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexId);
	}

	if (mHasNorMap)
	{
		// Bump mapping need to change space (world and TBN)
		// mTangentBuffer calculated by ComputeTangent() when normal texture has set
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i].mVboTangents);

		offset = 0;
		stride = sizeof(vec3);
		glEnableVertexAttribArray(V_ATTRIB_TANGENT);
		glVertexAttribPointer(V_ATTRIB_TANGENT, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

		glActiveTexture(GL_TEXTURE0 + TEX_POS_NORMAL);
		glBindTexture(GL_TEXTURE_2D, mTexNorId);
	}
	//}
}

void BasicRenderer::SetAtrib(int i) const
{
	//for(int i=0; i<=buffNum; i++){
	//int i=0;
	LOGI("BasicRenderer::RebindVbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i].mVboVertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[i].mVboIndices);

	int stride = sizeof(VertexStruct); // stride: sizeof(float) * number of components
	int offset = 0;
	glEnableVertexAttribArray(V_ATTRIB_POSITION);
	glVertexAttribPointer(V_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

	offset += sizeof(vec3);
	glEnableVertexAttribArray(V_ATTRIB_NORMAL);
	glVertexAttribPointer(V_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

	// If renderer has texture, we should enable vertex attribute for texCoord
	if (mHasTexture || mHasNorMap)
	{
		offset += sizeof(vec3);
		glEnableVertexAttribArray(V_ATTRIB_TEX);
		glVertexAttribPointer(V_ATTRIB_TEX, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexId);
	}

	if (mHasNorMap)
	{
		// Bump mapping need to change space (world and TBN)
		// mTangentBuffer calculated by ComputeTangent() when normal texture has set
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i].mVboTangents);

		offset = 0;
		stride = sizeof(vec3);
		glEnableVertexAttribArray(V_ATTRIB_TANGENT);
		glVertexAttribPointer(V_ATTRIB_TANGENT, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid *>(offset));

		glActiveTexture(GL_TEXTURE0 + TEX_POS_NORMAL);
		glBindTexture(GL_TEXTURE_2D, mTexNorId);
	}
	//}
}

mat4 BasicRenderer::GetInverseTranspose(const mat4& m) const
{
	return transpose(inverse(m));

}


void BasicRenderer::PassUniform(int i) const
{
	mat4 worldMat = vertexBuffer[i].worldMat;
	mat4 viewMat = mCamera->GetViewMat();
	mat4 projMat = mCamera->GetPerspectiveMat();
	mat4 invTransWorldMat = GetInverseTranspose(worldMat);

	vertexBuffer[i].mShader->SetUniform("worldMat", worldMat);
	vertexBuffer[i].mShader->SetUniform("viewMat", viewMat);
	vertexBuffer[i].mShader->SetUniform("projMat", projMat);
	vertexBuffer[i].mShader->SetUniform("invTransWorldMat", invTransWorldMat);
	vertexBuffer[i].mShader->SetUniform("s_tex0", 0);
	vertexBuffer[i].mShader->SetUniform("s_texNor", TEX_POS_NORMAL);
	vertexBuffer[i].mShader->SetUniform("s_texCube", TEX_POS_CUBEMAP);
	vertexBuffer[i].mShader->SetUniform("eyePos", mCamera->GetEye());
	vertexBuffer[i].mShader->SetUniform("lightPos", vec3(50.0f, 50.0f, 50.0f));
	vertexBuffer[i].mShader->SetUniform("materialDiff", vec3(0.8f, 1.0f, 0.7f));
	vertexBuffer[i].mShader->SetUniform("materialSpec", vec3(0.8f, 1.0f, 0.7f));
	vertexBuffer[i].mShader->SetUniform("materialAmbi", vec3(0.0f, 0.0f, 0.0f));
	vertexBuffer[i].mShader->SetUniform("materialEmit", vec3(0.0f, 0.0f, 0.0f));
	vertexBuffer[i].mShader->SetUniform("materialSh", 100.0f);
	vertexBuffer[i].mShader->SetUniform("sourceDiff", vec3(0.7f, 0.7f, 0.7f));
	vertexBuffer[i].mShader->SetUniform("sourceSpec", vec3(1.0f, 1.0f, 1.0f));
	vertexBuffer[i].mShader->SetUniform("sourceAmbi", vec3(0.0f, 0.0f, 0.0f));
}

void BasicRenderer::Draw() const
{
	for(int i=0; i< 27; i++){
		SetAtrib(i);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexBuffer[i].mIndexBuffer.size()), GL_UNSIGNED_SHORT, static_cast<GLvoid *>(NULL));
	}
}

void BasicRenderer::Draw(int i) const
{
		SetAtrib(i);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexBuffer[i].mIndexBuffer.size()), GL_UNSIGNED_SHORT, static_cast<GLvoid *>(NULL));
}


/*****************************
 ***** Utility functions *****
 *****************************/
void BasicRenderer::LogInfo() const
{
	print_gl_string("Version", GL_VERSION);
	print_gl_string("Vendor", GL_VENDOR);
	print_gl_string("Renderer", GL_RENDERER);
	print_gl_string("Extensions", GL_EXTENSIONS);
	print_gl_string("GLSLversion", GL_SHADING_LANGUAGE_VERSION);
}

void BasicRenderer::CountTickInit() const
{
	mTimer->InitTimer();
}

void BasicRenderer::ComputeTick()
{
	static double lastTick = 0;
	double currTick = mTimer->GetElapsedTime();
	mDeltaTime = currTick - lastTick;
	lastTick = currTick;
	//LOGI("Tick: %f\n", mDeltaTime);
}

/// Computes Tangent vector by using position and texCoord
//  These vectors will be used for making TBN rotation matrix
void BasicRenderer::ComputeTangent()
{
	vector<vec3> triTangents;

	// Compute Tangent Basis
	for (unsigned int i = 0; i < vertexBuffer[buffNum].mIndexBuffer.size(); i += 3)
	{
		vec3 p0 = vertexBuffer[buffNum].mVertexBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i)).pos;
		vec3 p1 = vertexBuffer[buffNum].mVertexBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i + 1)).pos;
		vec3 p2 = vertexBuffer[buffNum].mVertexBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i + 2)).pos;

		vec3 uv0 = vec3(vertexBuffer[buffNum].mVertexBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i)).tex, 0);
		vec3 uv1 = vec3(vertexBuffer[buffNum].mVertexBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i + 1)).tex, 0);
		vec3 uv2 = vec3(vertexBuffer[buffNum].mVertexBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i + 2)).tex, 0);

		vec3 deltaPos1 = p1 - p0;
		vec3 deltaPos2 = p2 - p0;

		vec3 deltaUV1 = uv1 - uv0;
		vec3 deltaUV2 = uv2 - uv0;

		// Compute the tangent
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		vec3 computedTangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

		triTangents.push_back(computedTangent);
		triTangents.push_back(computedTangent);
		triTangents.push_back(computedTangent);
	}

	// Initialize mTangents
	for (int i = 0; i < vertexBuffer[buffNum].mVertexBuffer.size(); ++i)
	{
		vertexBuffer[buffNum].mTangentBuffer.push_back(vec3(0));
	}

	// Accumulate tangents by indices
	for (unsigned int i = 0; i < vertexBuffer[buffNum].mIndexBuffer.size(); ++i)
	{
		vertexBuffer[buffNum].mTangentBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i))
			= vertexBuffer[buffNum].mTangentBuffer.at(vertexBuffer[buffNum].mIndexBuffer.at(i)) + triTangents.at(i);
	}
}

void BasicRenderer::ImportModel(char* objSource, BasicRenderer* renderer) const
{
	ImportModelScale(objSource, renderer, 1.0f);
}

void BasicRenderer::ImportModelScale(char* objSource, BasicRenderer* renderer, const float& scale) const
{
	LOGI("funcition : getObjModel\n");
	vec3 sVec = vec3(scale);

	vector<vec3> posCoords;
	vector<vec3> norCoords;
	vector<vec2> texCoords;

	vector<string> strIndexer;


	float x, y, z;
	char *line, *linePtr;
	line = util_strtok(objSource, "\r\n", &linePtr);
	while (line)
	{
		char *word, *wordPtr;
		word = util_strtok(line, " ", &wordPtr);

		switch (word[0])
		{
		case 'v':
			switch (word[1])
			{
			case 'n': //normal coordinate
				word = util_strtok(NULL, " ", &wordPtr);
				x = static_cast<float>(atof(word));
				word = util_strtok(NULL, " ", &wordPtr);
				y = static_cast<float>(atof(word));
				word = util_strtok(NULL, " ", &wordPtr);
				z = static_cast<float>(atof(word));
				norCoords.push_back(vec3(x, y, z));
				break;
			case 't': //texture coordinate
				word = util_strtok(NULL, " ", &wordPtr);
				x = static_cast<float>(atof(word));
				word = util_strtok(NULL, " ", &wordPtr);
				y = static_cast<float>(atof(word));
				texCoords.push_back(vec2(x, y));
				break;
			default: //vertex position
				word = util_strtok(NULL, " ", &wordPtr);
				x = static_cast<float>(atof(word));
				word = util_strtok(NULL, " ", &wordPtr);
				y = static_cast<float>(atof(word));
				word = util_strtok(NULL, " ", &wordPtr);
				z = static_cast<float>(atof(word));
				posCoords.push_back(sVec * vec3(x, y, z));
				break;
			}

			break;

		case 'f':
			while ((word = util_strtok(NULL, " ", &wordPtr)))
			{
				string face = word;
				vector<string>::iterator findIter = find(strIndexer.begin(),
				                                                   strIndexer.end(), word);

				if (findIter != strIndexer.end())
				{
					// this face already in vertex data
					renderer->vertexBuffer[buffNum].mIndexBuffer.push_back(std::distance(strIndexer.begin(), findIter));
				}
				else
				{
					unsigned short face_index = static_cast<unsigned short>(strIndexer.size());
					renderer->vertexBuffer[buffNum].mIndexBuffer.push_back(face_index);
					strIndexer.push_back(face);

					VertexStruct newVertex;
					char *num, *numPtr;
					num = util_strtok(word, "/", &numPtr); // position index
					newVertex.pos = posCoords.at(atoi(num) - 1);
					num = util_strtok(NULL, "/", &numPtr); // texture index
					newVertex.tex = texCoords.at(atoi(num) - 1);
					num = util_strtok(NULL, "/", &numPtr); // normal index
					newVertex.nor = norCoords.at(atoi(num) - 1);

					renderer->vertexBuffer[buffNum].mVertexBuffer.push_back(newVertex);
				}
			}

			break;

		case 'g':
			LOGI("name : %s\n", util_strtok(NULL, " ", &wordPtr));
			break;

		default:
			break;
		}
		line = util_strtok(NULL, "\r\n", &linePtr);
	}
}

vec3 BasicRenderer::GetArcballVector(const vec2& point) const
{
	const float RADIUS = 1.0;

	vec3 P = vec3(1.0 * point.x / mWidth * 2 - 1.0,
	              1.0 * point.y / mHeight * 2 - 1.0,
	              0);
	P.y = -P.y;

	float OP_squared = P.x * P.x + P.y * P.y;
	if (OP_squared <= RADIUS * RADIUS)
		P.z = sqrt(RADIUS * RADIUS - OP_squared); // Pythagore
	else
		P = glm::normalize(P); // nearest point

	return P;
}

mat4 BasicRenderer::GetWorldMatrix() const
{
	static quat startRotQuat = quat_cast(mat3(1));
	static quat lastRotQuat = startRotQuat;
	static vec2 ancPts = mTouchPoint;	//mTouchPoint
	static bool isUpdateAnc = false;

	if (mIsTouchOn)
	{
		if (!isUpdateAnc)
		{
			ancPts = mTouchPoint;
			isUpdateAnc = true;
			LOGI("Anchor Updated\n");
		}
		else
		{
			if (ancPts.x != mTouchPoint.x || ancPts.y != mTouchPoint.y)
			{
				// Get the vectors on the arcball
				vec3 va = GetArcballVector(ancPts);
				vec3 vb = GetArcballVector(mTouchPoint);

				// Get the rotation axis and the angle between the vector
				float angle = acos(glm::min(1.0f, dot(va, vb))) * 2.0f;

				vec3 axisInCameraSpace = normalize(cross(va, vb));

				mat4 cameraToObjectSpace = inverse(GetCamera()->GetViewMat());
				vec3 axisInObjectSpace = normalize(mat3(cameraToObjectSpace) * axisInCameraSpace);

				quat curRotQuat = angleAxis(angle, axisInObjectSpace);
				lastRotQuat = normalize(curRotQuat * startRotQuat);

			}
		}
	}
	else
	{
		startRotQuat = lastRotQuat;
		isUpdateAnc = false;
	}

	mat4 rotationMat = mat4_cast(lastRotQuat);

	return rotationMat;
}

