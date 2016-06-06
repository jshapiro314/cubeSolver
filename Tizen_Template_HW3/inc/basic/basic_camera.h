#ifndef __BASIC_CAMERA_H__
#define __BASIC_CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BasicCamera
{
private:
	const float TORADIAN;
	const float ROTATION_VEL = 45.0f;
	const float ZOOM_MIN_LENGTH = 5.0f;

	glm::vec3 mEye;
	float mDist;
	glm::vec3 mUp;
	glm::vec3 mFw;
	glm::vec3 mAngle; // yaw pitch, roll

	float m_zNear;
	float m_zFar;

	glm::vec3 mAt;

	glm::mat4 mPerspectiveMat;

public:
	BasicCamera();

	glm::mat4 GetViewMat() const;

	glm::mat4 GetPerspectiveMat() const;

	void ComputePerspective(const float& fovy, const int& w, const int& h);

	const glm::vec3 GetEye() const;

	const glm::vec3 GetAt() const;

	void SetEye(const float& x, const float& y, const float& z);

	void SetAt(const float& x, const float& y, const float& z);

	void RotateAuto(const double& deltaTime);

	void Rotate(const float& deltaX, const float& deltaY);

	void ZoomIn(const float& vel);

	void ZoomOut(const float& vel);

	void MoveForward(const float& vel);

	void MoveBackward(const float& vel);

	void MoveRight(const float& vel);

	void MoveLeft(const float& vel);

	void MoveUp(const float& vel);

	void MoveDown(const float& vel);

	void UpdateAt();

	void UpdateAngle();
};

inline glm::vec3 projToVector(const glm::vec3& target, const glm::vec3& axis)
{
	float numerator = glm::dot(target, axis);
	float denom = glm::length(axis);
	denom *= denom;
	denom = 1.0f / denom;
	return numerator * denom * axis;
}

inline glm::vec3 projToPlane(const glm::vec3& target, const glm::vec3& normal)
{
	return target - projToVector(target, normal);
}

inline float getAngle(const glm::vec3& a, const glm::vec3& b)
{
	return glm::acos(glm::dot(glm::normalize(a), glm::normalize(b)));
}


inline void limitAngle(float& angle)
{
	if (angle > 180.0f) angle -= 360.0f;
	else if (angle < -180.0f) angle += 360.0f;
}

inline glm::mat4 BasicCamera::GetViewMat() const
{
	return glm::lookAt(mEye, mAt, mUp);
}

inline glm::mat4 BasicCamera::GetPerspectiveMat() const
{
	return mPerspectiveMat;
}

inline void BasicCamera::ComputePerspective(const float& fovy, const int& w, const int& h)
{
	mPerspectiveMat = glm::perspective(fovy * TORADIAN, static_cast<float>(w) / static_cast<float>(h), m_zNear, m_zFar);
}

#endif //__BASIC_CAMERA_H__


