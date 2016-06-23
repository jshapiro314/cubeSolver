#include <glm/gtx/quaternion.hpp>

#include "basic/basic_camera.h"

using namespace glm;

BasicCamera::BasicCamera() :
	TORADIAN(pi<float>() / 180.0f),
	mEye(vec3(1500.0f, 250.0f, -1000.0f)),
	mDist(100.0f),
	mUp(vec3(0, 1.0f, 0.0f)),
	mFw(vec3(0, 0, -1.0f)),
	mAngle(vec3(0.0f, -45.0f, 0)),
	//        mUp(vec3(0, 0.0f, -1.0f)),
	m_zNear(2.0f),
	m_zFar(10000.0f),
	mAt(vec3(0)),
	mPerspectiveMat(mat4())
{
	//    UpdateAt();
	mAt = vec3(0, 0, 0);
	mDist = distance(mEye, mAt);
	UpdateAngle();
}

void BasicCamera::UpdateAngle()
{
	vec3 dir = mAt - mEye;
	vec3 projDir = projToPlane(dir, mUp);
	if (dot(dir, mUp) > 0)
	{
		mAngle.y = getAngle(projDir, dir) / TORADIAN; // pitch
	}
	else
	{
		mAngle.y = -getAngle(projDir, dir) / TORADIAN;
	}
	mAngle.x = getAngle(mFw, projDir) / TORADIAN; // yaw
}

void BasicCamera::UpdateAt()
{
	vec3 dir = mFw;

	quat qYaw = angleAxis(mAngle.x * TORADIAN, mUp);
	dir = toMat3(qYaw) * dir;
	vec3 pitchAxis = cross(dir, mUp);
	quat qPitch = angleAxis(mAngle.y * TORADIAN, pitchAxis);
	dir = toMat3(qPitch) * dir;
	mAt = dir * mDist + mEye;
}

void BasicCamera::RotateAuto(const double& deltaTime)
{
	float degree = ROTATION_VEL * deltaTime;

	// Add yaw angle;
	mAngle.x += degree;
	limitAngle(mAngle.x);

	vec3 prevAt = mAt;
	UpdateAt();

	vec3 deltaAt = prevAt - mAt;

	mAt = prevAt;
	mEye += deltaAt;
}

void BasicCamera::Rotate(const float& deltaX, const float& deltaY)
{
	mAngle.x += deltaX;
	mAngle.y += deltaY;
	limitAngle(mAngle.x);
	mAngle.y = clamp<float>(mAngle.y, -89.9, 89.9);
	UpdateAt();
}

void BasicCamera::ZoomIn(const float& vel)
{
	vec3 dir = mAt - mEye;
	float remain = glm::length(dir);
	remain -= ZOOM_MIN_LENGTH;
	dir = normalize(dir);

	remain = (remain > vel) ? vel : remain;
	dir *= remain;
	mEye += dir;
	mDist -= remain;
}

void BasicCamera::ZoomOut(const float& vel)
{
	vec3 dir = mEye - mAt;
	dir = normalize(dir);
	dir *= vel;
	mEye += dir;
	mDist += vel;
}


void BasicCamera::SetEye(const float& x, const float& y, const float& z)
{
	mEye.x = x;
	mEye.y = y;
	mEye.z = z;
	mDist = distance(mEye, mAt);
	UpdateAngle();
}

void BasicCamera::SetAt(const float& x, const float& y, const float& z)
{
	mAt.x = x;
	mAt.y = y;
	mAt.z = z;
	mDist = distance(mEye, mAt);
	UpdateAngle();
}

const glm::vec3 BasicCamera::GetEye() const
{
	return mEye;
}

const glm::vec3 BasicCamera::GetAt() const
{
	return mAt;
}

void BasicCamera::MoveForward(const float& vel)
{
	vec3 dir = mAt - mEye;
	dir = normalize(dir) * vel;
	mEye += dir;
	UpdateAt();
}

void BasicCamera::MoveBackward(const float& vel)
{
	vec3 dir = mEye - mAt;
	dir = normalize(dir) * vel;
	mEye += dir;
	UpdateAt();
}

void BasicCamera::MoveRight(const float& vel)
{
	vec3 dir = mEye - mAt;
	dir = normalize(dir);
	dir = -cross(mUp, dir) * vel;
	mEye += dir;
	UpdateAt();
}

void BasicCamera::MoveLeft(const float& vel)
{
	vec3 dir = mEye - mAt;
	dir = normalize(dir);
	dir = cross(mUp, dir) * vel;
	mEye += dir;
	UpdateAt();
}

void BasicCamera::MoveUp(const float& vel)
{
	vec3 dir = mUp * vel;
	mEye += dir;
	UpdateAt();
}

void BasicCamera::MoveDown(const float& vel)
{
	vec3 dir = -mUp * vel;
	mEye += dir;
	UpdateAt();
}

