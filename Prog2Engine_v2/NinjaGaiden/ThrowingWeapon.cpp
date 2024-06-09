#include "pch.h"
#include "ThrowingWeapon.h"

#include "TextureManager.h"

const int ThrowingWeapon::m_CELL_COUNT { 6 };
const float ThrowingWeapon::m_SCALE { 3.f };
const float ThrowingWeapon::m_FRAME_TIME { 0.25f };

ThrowingWeapon::ThrowingWeapon( ThrowingWeaponType type, const Point2f& position, const Vector2f& velocity, bool isFriend)
		: m_Type(type),
		m_TexturePtr(TexturesManager::GetInstance() -> GetTexture(TextureType::throwingWeapon)),
		m_Position(position),
		m_Velocity(velocity),
		m_IsFriend(isFriend)
{
	m_SourceRect = Rectf();
	m_InitFrameNr = static_cast<int>(m_Type);
	m_FrameNr = m_InitFrameNr;

	if (m_Type == ThrowingWeaponType::shurikenSmall || m_Type == ThrowingWeaponType::shurikenBig)
	{
		m_FramesCount = 2;
	}
	else
	{
		m_FramesCount = 1;
	}
	m_TextureCellWidth = 	m_TexturePtr->GetWidth() / 6;
}
void ThrowingWeapon::Update( float elapsedSec )
{
	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;

	UpdateSourceRect();
	ChangeFrames(elapsedSec);
	
	m_CollisionRect = Rectf(m_Position.x, m_Position.y, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE);
	if (m_Velocity.x < 0.f)
	{
		m_CollisionRect.left = m_CollisionRect.left + (m_TextureCellWidth - m_SourceRect.width ) * m_SCALE;
	}


}
void ThrowingWeapon::UpdateSourceRect( )
{
	float sourceRectWidth {m_TexturePtr->GetWidth() /  m_CELL_COUNT};
	float sourceRectHeight { m_TexturePtr->GetHeight()};

	if (m_Type == ThrowingWeaponType::shurikenSmall)
	{
		m_SourceRect.width = sourceRectWidth * 0.5f;
		m_SourceRect.height = sourceRectHeight* 0.5f;
	} else if (m_Type == ThrowingWeaponType::fire)
	{
		m_SourceRect.width = sourceRectWidth * 0.5f;
		m_SourceRect.height =sourceRectHeight;
	} else if (m_Type == ThrowingWeaponType::kunai)
	{
		m_SourceRect.width = sourceRectWidth * 0.5f;
		m_SourceRect.height = sourceRectHeight * 0.2f;
	}
	else
	{
		m_SourceRect.width = sourceRectWidth;
		m_SourceRect.height = sourceRectHeight;
	}
	
	
	m_SourceRect.left = (m_FrameNr % m_CELL_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = sourceRectHeight - m_SourceRect.height;

}
void ThrowingWeapon::ChangeFrames( float elapsedSec )
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FRAME_TIME)
	{
		m_AccuSec-= m_FRAME_TIME;

		++m_FrameNr;

		if (m_FrameNr >= m_FramesCount)
		{
			m_FrameNr = m_InitFrameNr;
		}
	}
}
Rectf ThrowingWeapon::GetCollisionRect( ) const
{
	return m_CollisionRect;
}
bool ThrowingWeapon::GetIsFriendly( ) const
{
	return m_IsFriend;
}
Vector2f ThrowingWeapon::GetThrowingWeaponVelocity( ) const
{
	return m_Velocity;
}

void ThrowingWeapon::Draw( ) const
{
	glPushMatrix();
	if (m_Velocity.x < 0.f)
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glTranslatef((m_TextureCellWidth) * m_SCALE, 0.f, 0.f);
		glScalef(-m_SCALE, m_SCALE, 1.f);
	}
	else
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
	}
	m_TexturePtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();
}


