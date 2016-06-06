#ifndef __BASIC_RENDERER_H__
#define __BASIC_RENDERER_H__

#include <vector>

#include "basic_gl_set.h"
#include "basic_utils.h"
#include "basic_camera.h"
#include "basic_texdata.h"
#include "basic_shader.h"
#include "basic_timer.h"

struct VertexStruct
{
	glm::vec3 pos;
	glm::vec3 nor;
	glm::vec2 tex;
};

struct VertBuff
{
	std::vector<VertexStruct> mVertexBuffer;
	std::vector<GLushort> mIndexBuffer;
	std::vector<glm::vec3> mTangentBuffer;

	GLuint mVboVertices;
	GLuint mVboIndices;
	GLuint mVboTangents;
	GLuint mVboInstTransforms;
};

class BasicRenderer
{
public:
	const int V_ATTRIB_POSITION = 0;
	const int V_ATTRIB_NORMAL = 1;
	const int V_ATTRIB_TEX = 2;
	const int V_ATTRIB_TANGENT = 3;
	const int V_ATTRIB_INSTPOSITION = 5;

	const int TEX_POS_NORMAL = 6;
	const int TEX_POS_CUBEMAP = 7;
	int buffNum;

protected:
	int mWidth;
	int mHeight;
	double mDeltaTime;



	BasicTimer* mTimer;
	BasicCamera* mCamera;
	BasicShader* mShader;

	bool mIsAutoRotateEye;
	bool mIsFill;

	bool mIsTouchOn;
	// Stores Touch Point x, y determined by scrolling screen
	glm::vec2 mTouchPoint;

	//vertex buffer class list
	VertBuff vertexBuffer[2];

	// vertex buffer
	//std::vector<VertexStruct> mVertexBuffer;
	//std::vector<GLushort> mIndexBuffer;
	//std::vector<glm::vec3> mTangentBuffer;

	// vertex buffer object and index buffer object
	//GLuint mVboVertices;
	//GLuint mVboIndices;
	//GLuint mVboTangents;
	//GLuint mVboInstTransforms;

	// variables for texture handling
	bool mHasTexture;
	bool mHasCubemap;
	bool mHasNorMap;
	bool mHasHeightmap;

	// Texture object id
	GLuint mTexId;
	GLuint mTexCubeId;
	GLuint mTexNorId;
	GLuint mTexHeightId;

	int mInstCount;


public:
	BasicRenderer();

	~BasicRenderer();

	// App interface functions
	// GLES20
	bool SetProgram(const std::string& vertexSource, const std::string& fragmentSource) const;

	bool SetProgram(const char* vertexSource, const char* fragmentSource) const;

	// GLES31
	bool SetProgram(const char* vertexSource, const char* tessControlSource, const char* tessEvalSource,
	                const char* geometrySource, const char* fragmentSource) const;

	void SetNewModel(const std::string& objSource, const float& scale);

	void SetNewModel(char* objSource);

	void SetNewModel(char* objSource, const float& scale);

	void SetTexture(TexData_Type type, const TexData* newTex);

	bool Initialize();

	void SetViewPort(int w, int h);

	void RenderFrame();

	// CANNOT USE IN GLES
	void TogglePolygonMode();


private: // Texture functions
	void CreateTexBuffer(const TexData& newTex, GLuint& target) const;

	void TexBuffer(GLenum type, const TexData& newTex) const;

private:// Rendering functions
	void SetState() const;

	void CreateVbo();

	void PassUniform() const;

	void Draw() const;

public:
	void RebindVbo() const;

private:// Utility functions
	void LogInfo() const;

	void CountTickInit() const;

	void ComputeTick();

	void ComputeTangent();

	void ImportModel(char* objSource, BasicRenderer* renderer) const;

	void ImportModelScale(char* objSource, BasicRenderer* renderer, const float& scale) const;

private:// Touch handling funtions
	glm::mat4 GetInverseTranspose(const glm::mat4& m) const;

	glm::vec3 GetArcballVector(const glm::vec2& point) const;

	glm::mat4 GetWorldMatrix() const;

public:// inline functions
	BasicCamera* GetCamera() const;

	void SetTouchPoint(const float& x, const float& y);

	void OnAutoRotate();

	void OffAutoRotate();

	void ToggleRotate();

	void TouchOn();

	void TouchOff();
};

inline BasicCamera* BasicRenderer::GetCamera() const
{
	return mCamera;
}

inline void BasicRenderer::SetTouchPoint(const float& x, const float& y)
{
	LOGI("Touch Point (x,y): (%f,%f)\n", x, y);
	mTouchPoint.x = x;
	mTouchPoint.y = y;
}

inline void BasicRenderer::OnAutoRotate()
{
	mIsAutoRotateEye = true;
}

inline void BasicRenderer::OffAutoRotate()
{
	mIsAutoRotateEye = false;
}

inline void BasicRenderer::ToggleRotate()
{
	mIsAutoRotateEye = !mIsAutoRotateEye;
}

inline void BasicRenderer::TouchOn()
{
	mIsTouchOn = true;
}

inline void BasicRenderer::TouchOff()
{
	mIsTouchOn = false;
}


#endif //__BASIC_RENDERER_H__


