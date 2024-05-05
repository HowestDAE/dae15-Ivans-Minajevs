#include "pch.h"
#include "KnifeMan.h"
KnifeMan::KnifeMan( float startPosX, float endPosX, const Ryu* ryuPtr, const TexturesManager* texturesManager, Point2f position, Point2f velocity ) :
				Enemy(startPosX, endPosX, ryuPtr, texturesManager, position, velocity)
{
}
void KnifeMan::UpdateSourceRect( )
{
	float sourceRectWidth {m_EnemiesTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_EnemiesTexturePtr->GetHeight() / m_ROWS};
	m_SourceRect.width = sourceRectHeight * 0.5f;
	if (m_FrameNr < 4)
	{
		
		m_SourceRect.height = sourceRectHeight * 0.8f;
	}
	else
	{
		m_SourceRect.height = sourceRectHeight * 0.6f;
	}
	
	m_SourceRect.left = (m_FrameNr % m_FRAMES_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = (static_cast<int>(EnemyType::knifeMan) + 1) * m_EnemiesTexturePtr->GetHeight() / m_ROWS - m_SourceRect.height;
}
void KnifeMan::ChangeFrames( float elapsedSec )
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

