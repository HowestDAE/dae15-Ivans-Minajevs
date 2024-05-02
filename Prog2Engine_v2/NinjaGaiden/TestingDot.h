#pragma once

class TestingDot
{
public:
	TestingDot(Point2f pos, float size);
	
	//~TestingDot();

	void Draw() const;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	bool GetIsAlive() const;
	Point2f GetPosition() const;
	
private:
	Point2f m_Position;
	Ellipsef m_Ellipse;
	bool m_IsAlive;
};
