#include "pch.h"
#include "Enemy.h"

#include "Trigger.h"
#include "utils.h"

Enemy::Enemy(const Ryu* ryuPtr, const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity) :
	m_Velocity(Point2f(horizontalVelocity, m_VERTICAL_VELOCITY)), m_TriggerPtr(triggerPtr), m_IsAlive(true), m_RyuPtr(ryuPtr)
{
	m_EnemyType = m_TriggerPtr->GetEnemyType();
	m_Position = m_TriggerPtr->GetPosition();
	m_MovementDirection = m_TriggerPtr->GetInitMovementDirection();

	m_EnemiesTexturePtr = texturesManagerPtr->GetTexture(TextureType::enemies);

	m_SourceRect = Rectf();
}

void Enemy::Draw( ) const
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	glPushMatrix();
	if (m_MovementDirection == MovementDirection::left)
	{
		glTranslatef(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y, 0.f);
		glScalef(-m_SCALE, m_SCALE, 1.f);
	}
	else
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
	}
	m_EnemiesTexturePtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();
	//utils::DrawRect(GetSourceRect(), 2.f);
}

void Enemy::Update( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec )
{
	ChangeFrames(elapsedSec);
	UpdateSourceRect();
	
	ChangePosition(elapsedSec);
	UpdateJump(elapsedSec);
	
	HandleVerticalCollision(mapVertices);
	HandleHorizontalCollision(mapVertices);
	//HandleBorders();
}

void Enemy::ChangePosition(float elapsedSec)
{
	if (m_MovementDirection == MovementDirection::left)
	{
		m_Position.x -= m_Velocity.x * elapsedSec;
	}
	else
	{
		m_Position.x += m_Velocity.x * elapsedSec;
	}

	m_Position.y += m_Velocity.y * elapsedSec;
}

void Enemy::HandleVerticalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices)
{
	utils::HitInfo hitInfoVertical;
	for (int index { 0 }; index < int(mapVertices.size()); ++index)
	{
		if (index < 2)
		{
			for (const std::vector<Point2f>& vertices : mapVertices[index])
			{
				if (utils::Raycast(vertices, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
								 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical) ||
					utils::Raycast(vertices, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f/ 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
								 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f / 4.f, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical))
				{
					if (m_Velocity.y < 0.f)
					{
						m_Velocity.y = 0;
						m_Position.y = hitInfoVertical.intersectPoint.y;
					}
				}
				if (m_EnemyType != EnemyType::dog)
				{
					if (utils::Raycast(vertices, Point2f(m_Position.x, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
									 Point2f(m_Position.x, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical) !=
						utils::Raycast(vertices, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE), m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
									 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE), m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical))
					{
						ChangeDirection();
					}
				}
			}
		}
	}
}
void Enemy::HandleHorizontalCollision( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices )
{
	utils::HitInfo hitInfoHorizontal;
	for (const std::vector<std::vector<Point2f>>& vertices : mapVertices)
	{
		for (const std::vector<Point2f> vertice : vertices)
		{
			if (utils::Raycast(vertice, Point2f(m_Position.x - 3.f, m_Position.y + 10.f),
		Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 3.f, m_Position.y + 10.f), hitInfoHorizontal))
			{
				ChangeDirection();
			}
		}
	}
}

void Enemy::ChangeDirection( )
{
	if (m_MovementDirection == MovementDirection::left)
	{
		m_Position.x += 3.f;
		m_MovementDirection = MovementDirection::right;
		
	}
	else if (m_MovementDirection == MovementDirection::right)
	{
		m_Position.x -= 3.f;
		m_MovementDirection = MovementDirection::left;
		
	}
}

void Enemy::UpdateJump(float elapsedSec)
{
	m_Velocity.y -= 32.f;
}
const Trigger * Enemy::GetTriggerPointer( ) const
{
	return m_TriggerPtr;
}

Point2f Enemy::GetPosition( ) const
{
	return m_Position;
}
Rectf Enemy::GetSourceRect( ) const
{
	return Rectf(m_Position.x, m_Position.y, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE);
}

bool Enemy::GetIsAlive( ) const
{
	return m_IsAlive;
}

void Enemy::SetIsAlive(bool isAlive)
{
	m_IsAlive = isAlive;
}
MovementDirection Enemy::GetDirection( ) const
{
	return m_MovementDirection;
}

