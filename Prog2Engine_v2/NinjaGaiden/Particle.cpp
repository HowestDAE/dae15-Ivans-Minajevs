#include "pch.h"
#include "Particle.h"
#include "Texture.h"

DeathParticle::DeathParticle( Point2f pos ) :
		m_Position(pos)
{
	m_DeathParticleSpriteSheetPtr = new Texture(m_FILE_PATH);
	InitSourceRect();
	
	m_AccuSec = 0;
	m_FramesPerSec = m_FRAMES_OF_ANIMATION;
	m_FrameTime	= 1.f / m_FramesPerSec;
	m_FrameNr = 0;
};

void DeathParticle::InitSourceRect()
{
	m_SourceRect.width  = m_DeathParticleSpriteSheetPtr->GetWidth() / m_FRAMES_OF_ANIMATION;
	m_SourceRect.height = m_DeathParticleSpriteSheetPtr->GetHeight();
	UpdateSourceRect();
}

void DeathParticle::UpdateSourceRect()
{
	m_SourceRect.left = float(m_FrameNr % m_FRAMES_OF_ANIMATION) * m_DeathParticleSpriteSheetPtr->GetWidth() / m_FRAMES_OF_ANIMATION;
	m_SourceRect.bottom = 0.f;
}

void DeathParticle::Update(float elapsedSec)
{
	ChangeFrames(elapsedSec);
	UpdateSourceRect();
}

void DeathParticle::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		m_DeathParticleSpriteSheetPtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();
}

void DeathParticle::ChangeFrames(float elapsedSec)
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

