#pragma once
#include "TriggersManager.h"
class Camera
{
public:
	explicit Camera(float screenWidth, float screenHeight);
	Camera& operator=(const Camera& rhs) = default;
	Camera(const Camera& other) = default;

	Rectf GetViewRect() const;
	void Update(float levelW, float levelH, Point2f trackCenter);
	
	void Reset();

private:
	float m_ScreenWidth;
	float m_ScreenHeight;
	Rectf m_ViewRect;
};

