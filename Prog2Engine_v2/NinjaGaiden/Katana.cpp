#include "pch.h"
#include "Katana.h"

#include "utils.h"

Katana::Katana( const TexturesManager* texturesManager, Point2f pos)  : m_Position(pos)
{
	m_KatanaSpriteSheetPtr = texturesManager->GetTexture(TextureType::katana);
	m_FrameNr = 0;
	m_IsActive = false;
	InitializeSourceRect();
}

/*Katana& Katana::operator=(const Katana& rhs)
{
	if (this != &rhs)
	{
		this->m_Position = rhs.m_Position;

		delete m_KatanaSpriteSheetPtr;
		m_KatanaSpriteSheetPtr = new Texture(m_FILE_NAME);

		this->m_FrameNr = rhs.m_FrameNr;
		this->m_SourceRect = rhs.m_SourceRect;
		this->m_IsActive = rhs.m_IsActive;
	}
	return *this;
}

Katana::Katana(const Katana& other)
{
	m_Position = other.m_Position;
	m_KatanaSpriteSheetPtr = new Texture(m_FILE_NAME);
	m_FrameNr = other.m_FrameNr;
	m_SourceRect = other.m_SourceRect;
	m_IsActive = other.m_IsActive;
}


Katana::~Katana()
{
	delete m_KatanaSpriteSheetPtr;
	m_KatanaSpriteSheetPtr = nullptr;
}*/

void Katana::InitializeSourceRect()
{
	m_SourceRect.width = m_KatanaSpriteSheetPtr->GetWidth() / m_MAX_FRAMES_OF_ANIMATION;
	m_SourceRect.height = m_KatanaSpriteSheetPtr->GetHeight();
	UpdateSourceRect();
}

void Katana::Draw(MovementDirection state) const
{
	glPushMatrix();
	if (state == MovementDirection::left)
	{
		glTranslatef(m_Position.x - 3.f, m_Position.y, 0.f);
		glScalef(-m_SCALE, m_SCALE, 1.f);

	}
	else
	{
		glTranslatef(m_Position.x + m_SourceRect.width * m_SCALE - 10.f, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
	}
	m_KatanaSpriteSheetPtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();

}

void Katana::ChangePosition(Point2f pos)
{
	m_Position = pos;
}
void Katana::Update(std::vector<Enemy*>& enemyArrPtr ) const
{
	if (m_IsActive)
	{
		CheckEnemiesHit(enemyArrPtr);
	}
}

Rectf Katana::GetSourceRect()
{
	return m_SourceRect;
}



void Katana::UpdateSourceRect()
{
	m_SourceRect.bottom = 0.f;
	m_SourceRect.left = (m_FrameNr % m_MAX_FRAMES_OF_ANIMATION) * m_KatanaSpriteSheetPtr->GetWidth() / m_MAX_FRAMES_OF_ANIMATION;
}

void Katana::ChangeFrames(int frameNr)
{
	m_FrameNr = frameNr;
}

void Katana::SetIsActive(bool isActive)
{
	m_IsActive = isActive;
}

void Katana::CheckEnemiesHit(std::vector<Enemy*>& enemyArrPtr) const
{
	for (Enemy* enemyPtr : enemyArrPtr)
	{
		if (enemyPtr != nullptr)
		{
			if (utils::IsOverlapping(enemyPtr->GetSourceRect(), m_SourceRect))
			{
				enemyPtr->SetIsAlive(false);
			}
		}
	}
}


