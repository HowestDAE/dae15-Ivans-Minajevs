#include "pch.h"
#include "Dog.h"

#include "EnemyType.h"
#include "utils.h"
Dog::Dog(const Ryu* ryuPtr, const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity) :
	Enemy(ryuPtr, texturesManagerPtr, triggerPtr, horizontalVelocity)
{
}

void Dog::UpdateSourceRect( )
{
	float sourceRectWidth {m_EnemiesTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_EnemiesTexturePtr->GetHeight() / m_ROWS};
	m_SourceRect.height = sourceRectHeight * 0.35f;
	if (m_FrameNr == 0)
	{
		
		m_SourceRect.width = sourceRectWidth * 0.625f;
	}
	else
	{
		m_SourceRect.width = sourceRectWidth;
	}
	
	m_SourceRect.left = (m_FrameNr % m_FRAMES_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = (static_cast<int>(EnemyType::dog) + 1) * m_EnemiesTexturePtr->GetHeight() / m_ROWS - m_SourceRect.height;
}

void Dog::ChangeFrames( float elapsedSec )
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FRAME_TIME)
	{
		m_AccuSec-= m_FRAME_TIME;

		++m_FrameNr;

		if (m_FrameNr >= m_FRAMES_COUNT)
		{
			m_FrameNr = 0;
		}
	}
}

