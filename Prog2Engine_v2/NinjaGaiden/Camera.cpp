#include "pch.h"
#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
}

void Camera::Aim(float levelW, float levelH, Point2f trackCenter) const
{
	float cameraX{ trackCenter.x - m_ScreenWidth / 2.f };

	if (cameraX < 0) cameraX = 0;
	else if (cameraX > levelW - m_ScreenWidth) cameraX = levelW - m_ScreenWidth;

	glPushMatrix();
	glTranslatef(-cameraX, 0.f, 0.0f);

}

void Camera::Reset()
{
	glPopMatrix();
	//return Point2f();
}
