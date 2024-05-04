#include "pch.h"
#include "Boxer.h"
Boxer::Boxer( float startPosX, float endPosX, const Ryu* ryuPtr, TexturesManager* texturesManager, Point2f position, Point2f velocity ) :
		Biker(startPosX, endPosX, ryuPtr, texturesManager, position, velocity) 
{
}
void Boxer::UpdateSourceRect( )
{
	float sourceRectWidth {m_EnemiesTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_EnemiesTexturePtr->GetHeight() / m_ROWS};
	m_SourceRect.height = sourceRectHeight * 0.8f;
	if (m_FrameNr == 2)
	{
		
		m_SourceRect.width = sourceRectWidth * 0.75f;
	}
	else
	{
		m_SourceRect.width = sourceRectWidth * 0.5f;
	}
	
	m_SourceRect.left = (m_FrameNr % m_FRAMES_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = (static_cast<int>(EnemyType::boxer) + 1) * m_EnemiesTexturePtr->GetHeight() / m_ROWS - m_SourceRect.height;	
}

