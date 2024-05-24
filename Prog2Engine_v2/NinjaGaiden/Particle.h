#pragma once
#include "Texture.h"
#include "ParticleType.h"
#include "TextureManager.h"
class Particle final
{
public:
	Particle(const TexturesManager* texturesManager, ParticleType particleType, Point2f pos, float timeAlive);
	
	void Draw() const;
	void Update(float elpasedSec);
	void ChangeTimeAlive(float newTimeAlive);
	float GetTimeAlive() const;

	//const int m_FRAMES_OF_ANIMATION{ 5 };
	const float m_FRAME_SIZE { 48 };
	const float m_SCALE { 3.f };
	//const std::string m_FILE_PATH {"death_particle.png"};

	
private:
	Texture* m_DeathParticleSpriteSheetPtr;
	ParticleType m_Type;
	
	int m_FramesOfAnimation;


	float m_TimeAlive;
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
