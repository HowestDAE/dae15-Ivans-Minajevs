#include "pch.h"
#include "Biker.h"

#include "EnemyType.h"

const int Biker::m_FRAMES_COUNT{ 3 };
const float Biker::m_HORIZONTAL_VELOCITY_BIKER{ 40.f };
const float Biker::m_FRAMES_PER_SEC { 5 };
const float Biker::m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };

Biker::Biker(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity):
	Enemy(texturesManagerPtr, triggerPtr, horizontalVelocity)
{
	//m_Velocity = Point2f( );
}
void Biker::UpdateSourceRect()
{
	float sourceRectWidth {m_EnemiesTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_EnemiesTexturePtr->GetHeight() / m_ROWS};
	if (m_FrameNr == 2)
	{
		m_SourceRect.height = sourceRectHeight;
		m_SourceRect.width = sourceRectWidth * 0.5f;
	}
	else
	{
		m_SourceRect.height = sourceRectHeight * 0.8f;
		m_SourceRect.width = sourceRectWidth * 0.75f;
	}
	
	m_SourceRect.left = (m_FrameNr % m_FRAMES_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = (static_cast<int>(EnemyType::biker) + 1) * m_EnemiesTexturePtr->GetHeight() / m_ROWS - m_SourceRect.height;	
}

void Biker::ChangeFrames( float elapsedSec )
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
int Biker::GetScoreIfKilled( )
{
	return 100;
}

