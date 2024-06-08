#include "pch.h"
#include "Katana.h"

#include "Boss.h"
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
	glTranslatef(m_Position.x, m_Position.y, 0.f);
	
	if (state == MovementDirection::left)
	{
		glRotatef(10.f, 0.f, 0.f, 1.f);
		glScalef(-m_SCALE, m_SCALE, 1.f);
	}
	else
	{
		glRotatef(-10.f, 0.f, 0.f, 1.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
		//glTranslatef(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y, 0.f);
	}
	
	m_KatanaSpriteSheetPtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();

}

void Katana::ChangePosition(Point2f pos)
{
	m_Position = pos;
}
void Katana::Update(LanternsManager* lanternsManagerPtr, EnemiesManager* enemiesManagerPtr, MovementDirection state, CollectiblesManager* collectiblesManagerPtr)
{
	Rectf sourceRect;
	if (state == MovementDirection::right)
	{
		sourceRect = Rectf(m_Position.x, m_Position.y - m_SourceRect.height, m_SourceRect.width * m_SCALE , m_SourceRect.height * m_SCALE);
	}
	else
	{
		sourceRect = Rectf(m_Position.x - m_SourceRect.width * m_SCALE, m_Position.y - m_SourceRect.height, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE);
	}
	if (m_IsActive)
	{
		for (Enemy* enemyPtr : enemiesManagerPtr->GetEnemiesArray())
		{
			if (enemyPtr != nullptr)
			{
				
				CheckEnemiesHit(enemyPtr, sourceRect);
			}
		}
		for (Lantern* lanternPtr : lanternsManagerPtr->GetLanternsArray())
		{
			if ( lanternPtr != nullptr)
			{
				
				CheckLanternsHit( lanternPtr, sourceRect, collectiblesManagerPtr);
			}
		}	
	}
}

Rectf Katana::GetSourceRect() const
{
	return m_SourceRect;
}
float Katana::GetScale( ) const
{
	return m_SCALE;
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
bool Katana::GetIsActivated( ) const
{
	return m_IsActive;
}

void Katana::CheckEnemiesHit( Enemy* enemyPtr, Rectf sourceRect)
{
	
	if (utils::IsOverlapping(enemyPtr->GetCollisionRect(), sourceRect))
	{
		
		if ( enemyPtr->GetEnemyType() == EnemyType::boss)
		{
			Boss::Hit();
			m_IsActive = false;
			//dynamic_cast<Boss*>(enemyPtr)->IsAttacked(false);
		}
		else
		{
			enemyPtr->SetIsAlive(false);
		}
	}
}
	

void Katana::CheckLanternsHit( Lantern* lanternPtr, Rectf sourceRect, CollectiblesManager* collectibleManagerPtr) const 
{
	if (utils::IsOverlapping(lanternPtr->GetSourceRect(), sourceRect))
	{
		collectibleManagerPtr->Add(new Collectible(lanternPtr->GetPosition(), lanternPtr->GetCollectibleType()));
		lanternPtr->SetIsExisting(false);
		lanternPtr->GetTriggerPointer()->SetIsAvailable(false);
	}
}


