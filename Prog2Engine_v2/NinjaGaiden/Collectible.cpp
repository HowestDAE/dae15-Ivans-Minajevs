#include "pch.h"
#include "Collectible.h"

#include <iostream>
#include <ostream>

#include "utils.h"
Collectible::Collectible( Point2f position, CollectibleType type)
	: m_Position(position), m_Type(type)
{
	
	m_CollectibleTexturePtr = TexturesManager::GetInstance()->GetTexture(TextureType::collectibles);
	
	UpdateSourceRect();
	m_Velocity = Point2f(0.f, 0.f);

	m_TimeAlive = 5.f;
}
void Collectible::Draw( ) const
{
	glPushMatrix();
	
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
		m_CollectibleTexturePtr->Draw(Point2f(), m_SourceRect);
	
	glPopMatrix();

	utils::DrawRect(m_Position, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE);
}
void Collectible::Update( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec )
{
	m_TimeAlive -= elapsedSec;
	
	
	if (m_TimeAlive < 0.f && !m_IsCollected)
	{
		m_IsExisting = false;
	}
	
	if (m_IsExisting)
	{
		if (!m_IsCollected)
		{
			UpdateJump(elapsedSec);
			m_Position.y += m_Velocity.y * elapsedSec;
			HandleVerticalCollision(mapVertices);
			
			
		}
	}
}
void Collectible::HandleVerticalCollision( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices )
{
	utils::HitInfo hitInfoVertical;
	for (int index { 0 }; index < int(mapVertices.size()); ++index)
	{
		for (const std::vector<Point2f>& vertices : mapVertices[index])
		{
			if (utils::Raycast(vertices, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
							 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical) ||
				utils::Raycast(vertices, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f/ 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
							 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f / 4.f, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical))
			{
				m_Velocity.y = 0;
				m_Position.y = hitInfoVertical.intersectPoint.y;
			}
		}
	}	
}
void Collectible::UpdateJump(float elapsedSec)
{
	m_Velocity.y -= 32.f;
}

void Collectible::UpdateSourceRect( )
{
	m_FrameNr = static_cast<int>(m_Type);
	
	float sourceRectWidth {m_CollectibleTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_CollectibleTexturePtr->GetHeight() / m_ROWS};
	
	m_SourceRect.left = (m_FrameNr % m_COLS) * sourceRectWidth;
	m_SourceRect.bottom = 0.f;
	m_SourceRect.width = sourceRectWidth;
	m_SourceRect.height = sourceRectHeight;
}
bool Collectible::GetIsExisting( ) const
{
	return m_IsExisting;
}
void Collectible::SetIsExisting(bool isExisting)
{
	m_IsExisting = isExisting;
}
void Collectible::SetIsCollected( bool isCollected )
{
	m_IsCollected = isCollected;
}
Rectf Collectible::GetRect( ) const
{
	return Rectf(m_Position.x, m_Position.y, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE);
}
