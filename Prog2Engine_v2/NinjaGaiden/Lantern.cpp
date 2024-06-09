#include "pch.h"
#include "Lantern.h"

#include "utils.h"

const float Lantern::m_SCALE{ 2.8f };
const int Lantern::m_FRAMES_PER_SEC { 4 };
const float Lantern::m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
const int Lantern::m_COLS { 10 };
const int Lantern::m_ROWS { 2 };
const int Lantern::m_FRAMES_COUNT { 2 };

Lantern::Lantern( Point2f position, CollectibleType collectibleType, Trigger* triggerPtr, const TexturesManager* texturesManagerPtr )
	: m_TriggerPtr(triggerPtr), m_Position(position), m_CollectibleType(collectibleType)
{
	m_LanternTexturePtr = texturesManagerPtr->GetTexture(TextureType::collectibles);
	UpdateSourceRect( );
}
void Lantern::Update( float elapsedSec )
{
	UpdateSourceRect();
	ChangeFrames(elapsedSec);
}

void Lantern::Draw( ) const
{
	glPushMatrix();
	
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);

		m_LanternTexturePtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();
	utils::DrawRect(GetSourceRect());
}
void Lantern::UpdateSourceRect( )
{
	float sourceRectWidth {m_LanternTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_LanternTexturePtr->GetHeight() / m_ROWS};
	
	m_SourceRect.left = (m_FrameNr % m_FRAMES_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = sourceRectHeight;
	m_SourceRect.width = sourceRectWidth;
	m_SourceRect.height = sourceRectHeight;
}
void Lantern::ChangeFrames( float elapsedSec )
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
void Lantern::SetIsExisting( bool isExisting )
{
	m_IsExisting = isExisting;
}

Point2f Lantern::GetPosition( ) const
{
	return m_Position;
}
CollectibleType Lantern::GetCollectibleType( ) const
{
	return m_CollectibleType;
}
bool Lantern::GetIsExisting( ) const
{
	return m_IsExisting;
}
Rectf Lantern::GetSourceRect( ) const
{
	return Rectf(m_Position.x, m_Position.y, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE);
}

Trigger* Lantern::GetTriggerPointer( ) const
{
	return m_TriggerPtr;
}


