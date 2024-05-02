#include "pch.h"
#include "Particle.h"
#include "ParticleType.h"
#include "Texture.h"

Particle::Particle(ParticleType type, Point2f pos, float timeAlive) :
		m_Type(type), m_Position(pos), m_TimeAlive(timeAlive) 
{
	m_DeathParticleSpriteSheetPtr = new Texture(m_FILE_PATH);
	InitSourceRect();
	
	m_AccuSec = 0;
	m_FramesPerSec = int(m_FRAMES_OF_ANIMATION / m_TimeAlive);
	m_FrameTime	= 1.f / m_FramesPerSec;
	m_FrameNr = 0;
};

Particle::~Particle()
{
	delete m_DeathParticleSpriteSheetPtr;
	m_DeathParticleSpriteSheetPtr = nullptr;
}

void Particle::InitSourceRect()
{
	m_SourceRect.width  = m_DeathParticleSpriteSheetPtr->GetWidth() / m_FRAMES_OF_ANIMATION;
	m_SourceRect.height = m_DeathParticleSpriteSheetPtr->GetHeight();
	UpdateSourceRect();
}

void Particle::UpdateSourceRect()
{
	m_SourceRect.left = float(m_FrameNr % m_FRAMES_OF_ANIMATION) * m_DeathParticleSpriteSheetPtr->GetWidth() / m_FRAMES_OF_ANIMATION;
	m_SourceRect.bottom = m_FRAME_SIZE * float(static_cast<int>(m_Type) + 1) - m_FRAME_SIZE;	//check if can be optimised
}

void Particle::Update(float elapsedSec)
{
	ChangeFrames(elapsedSec);
	UpdateSourceRect();
}

void Particle::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
		glTranslatef(-m_FRAME_SIZE / 2.f, -m_FRAME_SIZE / 2.f, 0.f);
		m_DeathParticleSpriteSheetPtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();
}

void Particle::ChangeFrames(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FrameTime)
	{
		m_AccuSec-= m_FrameTime;
		++m_FrameNr;
		
		if (m_FrameNr >= m_FRAMES_OF_ANIMATION)
		{
			m_FrameNr = 0;
		}
	}
}

void Particle::ChangeTimeAlive(float newTimeAlive)
{
	m_TimeAlive = newTimeAlive;
}

float Particle::GetTimeAlive() const
{
	return m_TimeAlive;
}
