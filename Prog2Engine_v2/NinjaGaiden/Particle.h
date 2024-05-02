#pragma once
#include "Texture.h"

class DeathParticle
{
public:
	DeathParticle(Point2f pos);

	void Draw() const;
	void Update(float elpasedSec);

	const int m_FRAMES_OF_ANIMATION{ 5 };
	//const float m_FRAME_SIZE { 48 };
	const std::string m_FILE_PATH {"death_particle.png"};
private:
	Texture* m_DeathParticleSpriteSheetPtr;
	Point2f m_Position;
	Rectf m_SourceRect;

	int m_FrameNr;
	float m_AccuSec;
	int	  m_FramesPerSec;
	float m_FrameTime;

	void InitSourceRect();
	void UpdateSourceRect();
	//void ChangeMaxFramesOfAnimation();
	void ChangeFrames(float elapsedSec);
};
