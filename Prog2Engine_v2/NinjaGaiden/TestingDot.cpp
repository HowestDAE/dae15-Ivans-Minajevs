#include "pch.h"
#include "TestingDot.h"
#include "utils.h"

TestingDot::TestingDot(Point2f pos, float size) : m_Position(pos)
{
	m_Ellipse = Ellipsef(m_Position, size, size);
	m_IsAlive = true;
}


void TestingDot::Draw() const
{
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(m_Ellipse);
}

void TestingDot::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_IsAlive = false;
	}
}
bool TestingDot::GetIsAlive() const
{
	return m_IsAlive;
}

Point2f TestingDot::GetPosition() const
{
	return m_Position;
}