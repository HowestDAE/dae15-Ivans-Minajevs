#include "pch.h"
#include "Biker.h"
Biker::Biker(float startPosX, float endPosX,const Ryu* ryuPtr, TexturesManager* texturesManager, Point2f position, Point2f velocity) :
	Enemy(startPosX, endPosX, ryuPtr, texturesManager, position, velocity) 
{
}
void Biker::Update( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec )
{
	ChangeFrames(elapsedSec);
	UpdateSourceRect();
	
	ChangePosition(elapsedSec);
	UpdateJump(elapsedSec);
	
	HandleVerticalCollision(mapVertices);
	HandleHorizontalCollision(mapVertices);
	HandleBorders();
	
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
