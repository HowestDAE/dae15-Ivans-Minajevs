#include "pch.h"
#include "Camera.h"

#include "utils.h"

Camera::Camera(float screenWidth, float screenHeight) :
	m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
{
	m_ViewRect = Rectf();
}

Rectf Camera::GetViewRect( ) const
{
	return m_ViewRect;
}

void Camera::Update(float levelW, float levelH, Point2f trackCenter)
{
	float cameraX{ trackCenter.x - m_ScreenWidth / 2.f };

	if (cameraX < 0) cameraX = 0;
	else if (cameraX > levelW - m_ScreenWidth) cameraX = levelW - m_ScreenWidth;


	m_ViewRect = Rectf(cameraX, 0.f, m_ScreenWidth, m_ScreenHeight);
	

	glPushMatrix();
	glTranslatef(-cameraX, 0.f, 0.0f);

}

void Camera::Reset()
{
	glPopMatrix();
	//return Point2f();
}
