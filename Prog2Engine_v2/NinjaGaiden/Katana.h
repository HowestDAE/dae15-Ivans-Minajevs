#pragma once
#include <Texture.h>
#include "Ryu.h"
class Katana final
{
public:

	explicit Katana(Point2f pos);
	Katana& operator=(const Katana& rhs);
	Katana(const Katana& other);

	void Draw(Ryu::RyuMovementDirection state) const;
	void ChangePosition(Point2f pos);

	Rectf GetSourceRect();

	void InitializeSourceRect();
	void UpdateSourceRect();
	void ChangeFrames(int frameNr);

	~Katana();

	const int m_MAX_FRAMES_OF_ANIMATION{ 2 };
	const float m_SCALE{ 0.5 };
	const std::string m_FILE_NAME{ "katana_spritesheet.png" };
	
private:
	Point2f m_Position;
	int m_FrameNr;
	Texture* m_KatanaSpriteSheetPtr;
	Rectf m_SourceRect;
};

