#include "pch.h"
#include "Ryu.h"
#include "Katana.h"
#include <utils.h>
#include <iostream>

#include "Enemy.h"
#include "SoundEffectsManager.h"
Ryu::Ryu(const TexturesManager* texturesManager, Point2f pos)
{
	m_JumpActionsCounter = 0;
	m_AttackActionCounter = 0;
	m_MovementDirection = MovementDirection::right;
	m_State				= RyuState::none;
	m_IsMoving			= false;

	m_RyuSpriteSheetPtr	= texturesManager->GetTexture(TextureType::ryu);
	InitializeSourceRect();
	

	m_Position			= pos;

	m_AccuSec			= 0;
	m_FramesPerSec		= 12;
	m_FrameTime			= 1.f / float(m_FramesPerSec);

	m_FrameNr = 0;
	m_MaxFramesOfAnimation = 1;

	m_Velocity = Vector2f(0.f, 0.f);

	m_AttackSound = SoundEffectsManager::GetInstance()->GetSoundEffect(SoundEffectType::attack);
	m_HitSound =  SoundEffectsManager::GetInstance()->GetSoundEffect(SoundEffectType::ryuHit);
	m_JumpSound =  SoundEffectsManager::GetInstance()->GetSoundEffect(SoundEffectType::jump);
	m_CollectibleTake = SoundEffectsManager::GetInstance()->GetSoundEffect(SoundEffectType::collectibleTake);
	
	m_KatanaPtr = new Katana(texturesManager, Point2f(m_SourceRect.left + m_SourceRect.bottom, m_SourceRect.bottom + m_SourceRect.height));
}

Ryu::Ryu(const TexturesManager* texturesManager, float posX, float posY) : Ryu(texturesManager, Point2f{posX, posY})
{
}

Ryu::~Ryu()
{

	delete m_KatanaPtr;
}

//Ryu::Ryu(const Ryu& other) :
//	m_MovementDirection{ other.m_MovementDirection },
//	m_State{ other.m_State },
//	m_IsMoving { other.m_IsMoving },
//	m_RyuSpriteSheetPtr { new Texture("ryu_spritesheet.png") },
//	m_KatanaPtr{ new Katana(Point2f(m_SourceRect.left, m_SourceRect.bottom + m_SourceRect.height)) },
//	m_SourceRect { other.m_SourceRect },
//	m_Position{ other.m_Position },
//	m_Velocity{ other.m_Velocity },
//	//m_VerticalPosBeforeJump { other.m_VerticalPosBeforeJump },
//	m_AccuSec { other.m_AccuSec },
//	m_FramesPerSec { other.m_FramesPerSec },
//	m_FrameTime{ other.m_FrameTime },
//	m_FrameNr { other.m_FrameNr},
//	m_MaxFramesOfAnimation { other.m_MaxFramesOfAnimation }
//{
//
//}
//
//
//Ryu& Ryu::operator=(const Ryu& rhs)
//{
//	if (this != &rhs)
//	{
//		this->m_MovementDirection = rhs.m_MovementDirection;
//		this->m_State = rhs.m_State;
//		this->m_IsMoving = rhs.m_IsMoving;
//
//		delete this->m_RyuSpriteSheetPtr;
//		this->m_RyuSpriteSheetPtr = new Texture("ryu_spritesheet.png");
//
//		delete this->m_KatanaPtr;
//		this->m_KatanaPtr = new Katana(Point2f(m_SourceRect.left, m_SourceRect.bottom + m_SourceRect.height));
//
//		this->m_SourceRect = rhs.m_SourceRect;
//		this->m_Position = rhs.m_Position;
//		this->m_Velocity = rhs.m_Velocity;
//
//		//this->m_VerticalPosBeforeJump = rhs.m_VerticalPosBeforeJump;
//		this->m_AccuSec = rhs.m_AccuSec;
//		this->m_FramesPerSec = rhs.m_FramesPerSec;
//		this->m_FrameTime = rhs.m_FrameTime;
//		this->m_FrameNr = rhs.m_FrameNr;
//		this->m_MaxFramesOfAnimation = rhs.m_MaxFramesOfAnimation;
//	}
//	return *this;
//}
//

//Ryu::~Ryu()
//{
//	//delete m_RyuSpriteSheetPtr;
//	//m_RyuSpriteSheetPtr = nullptr;
//	delete m_KatanaPtr;
//}

void Ryu::InitializeSourceRect()
{
	m_SourceRect.width  = m_FRAME_WIDTH;
	m_SourceRect.height = m_FRAME_HEIGHT;
	UpdateSourceRect();
}

void Ryu::UpdateSourceRect()
{	
	m_SourceRect.left = (m_FrameNr % m_MaxFramesOfAnimation) * m_RyuSpriteSheetPtr->GetWidth() / m_COLS;
	
	if (m_State == RyuState::duckAttacking || m_State == RyuState::ducking)
	{
		m_SourceRect.height = m_FRAME_HEIGHT * 0.8f;
		m_SourceRect.bottom = (static_cast<int>(m_State) + 1) * m_RyuSpriteSheetPtr->GetHeight() / m_ROWS - m_FRAME_HEIGHT + m_FRAME_HEIGHT * 0.2f;

	}
	else
	{
		m_SourceRect.height = m_FRAME_HEIGHT;
		m_SourceRect.bottom = (static_cast<int>(m_State) + 1) * m_RyuSpriteSheetPtr->GetHeight() / m_ROWS - m_FRAME_HEIGHT;	
	}

	if (m_State == RyuState::attacking || m_State == RyuState::duckAttacking)
	{
		m_SourceRect.width = m_FRAME_WIDTH * 0.8f;
	}
	else if (m_State == RyuState::climbing || m_State == RyuState::jumping)
	{
		m_SourceRect.width = m_FRAME_WIDTH * 0.55f;
	}
	else if (m_State == RyuState::walking)
	{
		m_SourceRect.width = m_FRAME_WIDTH * 0.8f;
	}
	else
	{
		m_SourceRect.width = m_FRAME_WIDTH * 0.6f;
	}
}



void Ryu::ChangeDirection(MovementDirection direction)
{
	m_MovementDirection = direction;
}


void Ryu::Draw() const
{
	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking) && m_FrameNr > 0) m_KatanaPtr->Draw(m_MovementDirection);
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
	m_RyuSpriteSheetPtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();
}

void Ryu::Update(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, CollectiblesManager*  collectiblesManagerPtr, EnemiesManager* enemiesManagerPtr,  LanternsManager* lanternsManagerPtr)
{
	Rectf sourceRect {Rectf(m_Position.x, m_Position.y, m_SourceRect.width * m_SCALE, m_SourceRect.height * m_SCALE)};
	
	for (Collectible* collectiblePtr: collectiblesManagerPtr->GetCollectiblesArray())
	{
		if (collectiblePtr != nullptr)
		{
			if (utils::IsOverlapping(sourceRect, collectiblePtr->GetRect()))
			{
				collectiblePtr->SetIsExisting(false);
				m_CollectibleTake->Play(0);
			}
		}
	}
	if (m_State == RyuState::attacking || m_State == RyuState::duckAttacking)
	{
		m_FramesPerSec = 8;
	}
	else
	{
		m_FramesPerSec = 12;
	}
	
	m_FrameTime			= 1.f / float(m_FramesPerSec);
	
	
	for (Enemy* enemyPtr: enemiesManagerPtr->GetEnemiesArray())
	{
		if (enemyPtr != nullptr)
		{
			if (utils::IsOverlapping(enemyPtr->GetCollisionRect(), sourceRect))
			{
				if (m_State != RyuState::hurt)
				{
					m_State = RyuState::hurt;
					m_HitSound->Play(0);
					m_Health--;
					m_Velocity.y = 700.f;
					float intersectMin, intersectMax;
					utils::IntersectRectLine(enemyPtr->GetCollisionRect(), Point2f(m_Position.x - 1.f, m_Position.y),
											Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 1.f, m_Position.y), intersectMin, intersectMax);
					if ( intersectMin >= 0)
					{
						m_Velocity.x = -150.f;
					} else if (intersectMin < 0)
					{
						m_Velocity.x = 150.f;
					}
				}
			}	
		}
		
		
	}

	if (m_State != RyuState::hurt)
	{
		m_PlannedJumpDirection = m_MovementDirection;
		if (m_State != RyuState::attacking && m_State != RyuState::duckAttacking)
		{
			if (m_State != RyuState::jumping && m_State != RyuState::climbing)
			{
				m_State = RyuState::none;
				
			}
			m_Velocity.x = 0;
			if (pStates[SDL_SCANCODE_RIGHT])
			{
				if (m_State != RyuState::climbing)
				{
					m_Velocity.x = m_SPEED;
					if (m_State != RyuState::jumping)
					{
						m_State = RyuState::walking;
					}
					else
					{
						if (m_MovementDirection != MovementDirection::right)
						{
							m_Velocity.x = m_SPEED / 2.f;
						}
					}
					ChangeDirection(MovementDirection::right);
				}
				else
				{
					m_PlannedJumpDirection = MovementDirection::right;
				}


			}
			else if (pStates[SDL_SCANCODE_LEFT])
			{
				if (m_State != RyuState::climbing)
				{
					m_Velocity.x = -m_SPEED;
					if (m_State != RyuState::jumping)
					{
						m_State = RyuState::walking;
					}
					else
					{
						if (m_MovementDirection != MovementDirection::left)
						{
							m_Velocity.x = -m_SPEED / 2.f;
						}
					}
					ChangeDirection(MovementDirection::left);
				}
				else
				{
					m_PlannedJumpDirection = MovementDirection::left;
				}
			}
			if (pStates[SDL_SCANCODE_DOWN])
			{
				if (m_State != RyuState::climbing)
				{
					if (m_State != RyuState::walking && m_State != RyuState::jumping)
					{
						m_State = RyuState::ducking;
						m_Velocity.x = 0.f;
					}
				}
			}
		
			if (pStates[SDL_SCANCODE_X])
			{
				
					
				if (m_State == RyuState::climbing)
				{
					if (m_MovementDirection != m_PlannedJumpDirection)
					{
						m_MovementDirection = m_PlannedJumpDirection;
						m_Velocity.y = m_INIT_JUMP_SPEED;
						m_State = RyuState::jumping;
						m_JumpSound->Play(0);
						if (m_PlannedJumpDirection == MovementDirection::left)
						{
							m_Position.x -= 2.f;
						}
						else
						{
							m_Position.x += 2.f;
						}
						m_JumpActionsCounter += 1;
						
					}
				}
				if (m_JumpActionsCounter == 0)
				{
					if (m_State != RyuState::jumping && m_State != RyuState::climbing && m_State != RyuState::attacking)
					{
						m_Velocity.y = 893.f;
						m_State = RyuState::jumping;
						m_JumpSound->Play(0);
					}
					m_JumpActionsCounter += 1;
				
				}
			}
		}
	}
	
	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking || m_State == RyuState::climbing)) m_Velocity.x = 0.f;
	

	ChangePosition(elapsedSec);
	ChangeMaxFramesOfAnimation();
	ChangeFrames(elapsedSec);

	UpdateJump(elapsedSec);
	UpdateSourceRect();
	m_KatanaPtr->Update(lanternsManagerPtr, enemiesManagerPtr, m_MovementDirection, collectiblesManagerPtr);
	m_KatanaPtr->UpdateSourceRect();


	HandleFloorCollision(mapVertices[0]);
	HandlePlatformsCollision(mapVertices[1]);
	HandleSignsCollision(mapVertices[2]);
	HandleWallsCollision(mapVertices[3]);

	if (m_State == RyuState::climbing) m_Velocity.y = 0.f;
	if (m_Velocity.y != 0.f && m_State!=RyuState::attacking && m_State!=RyuState::hurt) m_State = RyuState::jumping;
}

#pragma region Handle Collision
void Ryu::HandleFloorCollision(const std::vector<std::vector<Point2f>>& vertices)
{
	utils::HitInfo hitInfoVertical;
	utils::HitInfo hitInfoHorizontal;

	if (utils::Raycast(vertices[0], Point2f(m_Position.x - 1.f, m_Position.y + 10.f),
		Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 1.f, m_Position.y + 10.f), hitInfoHorizontal))
	{
		if (m_State == RyuState::jumping)
		{
			if (m_Velocity.y < 500.f)
			{
				m_Position.y = hitInfoHorizontal.intersectPoint.y - 10.f;
				std::cout << hitInfoHorizontal.lambda << "\n";
				if ((m_MovementDirection == MovementDirection::left &&  hitInfoHorizontal.lambda <= 0.1f) ||
					(m_MovementDirection == MovementDirection::right &&  hitInfoHorizontal.lambda >= 0.9f))
				{
					m_State = RyuState::climbing;
				}
			}
		}

		m_Position.x = hitInfoHorizontal.intersectPoint.x;
		if (m_MovementDirection == MovementDirection::right)
		{
			//m_State = RyuState::walking;
			m_Position.x -= (m_SourceRect.width * m_SCALE + 1.f);
		}
		else if (m_MovementDirection == MovementDirection::left)
		{
			m_Position.x += 1.f;
		}
		m_Velocity.x = 0;
	}

	if (utils::Raycast(vertices[0], Point2f(m_Position.x, m_Position.y + m_SourceRect.height * m_SCALE),
		Point2f(m_Position.x, m_Position.y), hitInfoVertical) ||
		utils::Raycast(vertices[0], Point2f(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y + m_SourceRect.height * m_SCALE),
		Point2f(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y), hitInfoVertical))
	{
		if (m_Velocity.y <= 1.f)
		{
			m_Velocity.y = 0;
			m_Position.y = hitInfoVertical.intersectPoint.y;
			if (m_State == RyuState::jumping || m_State == RyuState::climbing || m_State == RyuState::hurt)
			{
				m_State = RyuState::none;
			}
		}
	}	

	
}

void Ryu::HandleSignsCollision(const std::vector<std::vector<Point2f>>& vertices)
{
	utils::HitInfo hitInfoHorizontal;
	utils::HitInfo hitInfoVertical;
	for (const std::vector<Point2f>& sign : vertices)
	{
		if (utils::Raycast(sign, Point2f(m_Position.x - 1.f, m_Position.y + 10.f), 
								 Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 1.f, m_Position.y + 10.f), hitInfoHorizontal))
		{
			if (m_Velocity.x * hitInfoHorizontal.normal.x < 0)
			{
				if (m_State == RyuState::jumping)
				{
					if (m_Velocity.y < 500.f)
					{
						m_Position.y = hitInfoHorizontal.intersectPoint.y - 10.f;
						m_State = RyuState::climbing;
					}
				}

				m_Velocity.x = 0;
				m_Position.x = hitInfoHorizontal.intersectPoint.x;

				if (m_MovementDirection == MovementDirection::right)
				{
					m_Position.x -= (m_SourceRect.width * m_SCALE + 1.f);
				}
				else
				{
					m_Position.x++;
				}
			}
		}
		if (utils::Raycast(sign, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
								 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical) ||
			utils::Raycast(sign, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f/ 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 2.f), 
								 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f / 4.f, m_Position.y - m_SourceRect.height * m_SCALE / 2.f), hitInfoVertical))
		{
			if (m_Velocity.y < 0.f)
			{
				if (m_Velocity.y * hitInfoVertical.normal.y < 0)
				{
					if (hitInfoVertical.lambda > 0.4f)
					{
						m_Position.y = hitInfoVertical.intersectPoint.y;
						if (m_State == RyuState::jumping || m_State == RyuState::hurt) m_State = RyuState::none;
						m_Velocity.y = 0;
					}
				}
			}
		}
	}
}

void Ryu::HandlePlatformsCollision(const std::vector<std::vector<Point2f>>& vertices)
{
	utils::HitInfo hitInfoVertical;
	for (const std::vector<Point2f>& platform : vertices)
	{
		if (utils::Raycast(platform, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 10.f), 
									 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) / 4.f, m_Position.y), hitInfoVertical) ||
			utils::Raycast(platform, Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f / 4.f, m_Position.y + m_SourceRect.height * m_SCALE / 10.f), 
									 Point2f(m_Position.x + (m_SourceRect.width * m_SCALE) * 3.f / 4.f, m_Position.y), hitInfoVertical))
		{
			if (m_Velocity.y < 0.f)
			{
				m_Position.y = hitInfoVertical.intersectPoint.y;
				if (m_State == RyuState::jumping || m_State == RyuState::hurt)
				{
					m_State = RyuState::none;
				}
				m_Velocity.y = 0;
			}
		}
	}
}



void Ryu::HandleWallsCollision(const std::vector<std::vector<Point2f>>& vertices)
{
	utils::HitInfo hitInfoHorizontal;
	for (const std::vector<Point2f>& walls : vertices)
	if (m_MovementDirection == MovementDirection::left)
	{

		if (utils::Raycast(walls, Point2f(m_Position.x - 1.f, m_Position.y + 10.f), 
								  Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 1.f, m_Position.y + 10.f), hitInfoHorizontal))
		{
			if (m_Velocity.x * hitInfoHorizontal.normal.x < 0.f)
			{
				if (m_State == RyuState::jumping)
				{
					m_Position.y = hitInfoHorizontal.intersectPoint.y - 10.f;
					m_State = RyuState::climbing;
				}
				m_Velocity.x = 0;
				m_Position.x = hitInfoHorizontal.intersectPoint.x;

				if (m_MovementDirection == MovementDirection::right)
				{
					m_Position.x -= (m_SourceRect.width * m_SCALE + 1.f);
				}
				else
				{
					m_Position.x++;
				}
			}
			
		}
	}
}
#pragma endregion


void Ryu::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_z:
		if (m_State != RyuState::climbing && m_State != RyuState::hurt)
		{
			if (m_AttackActionCounter == 0)
			{
				if (m_State != RyuState::attacking && m_State != RyuState::duckAttacking)
				{
					m_FrameNr = 0;
					if (m_State == RyuState::ducking)
					{
						m_State = RyuState::duckAttacking;
					}
					else
					{
						m_State = RyuState::attacking;
					}
					m_AttackSound->Play(0);
					m_AttackActionCounter += 1;
				}
			}
			break;
		}
	}
}
void Ryu::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (e.keysym.sym == SDLK_x)
	{
		m_JumpActionsCounter = 0;
		std::cout << m_JumpActionsCounter << std::endl;
		
	}
	if (e.keysym.sym == SDLK_z)
	{
		m_AttackActionCounter = 0;
	}

}
void Ryu::ResetHealth( )
{
	m_Health = Game::m_INIT_HEALTH;
}

void Ryu::SetPosition( const Point2f pos)
{
	m_Position = pos;
}

int Ryu::GetHealth( ) const
{
	return m_Health;
}


Point2f Ryu::GetPosition() const
{
	return m_Position;
}
Rectf Ryu::GetRect( ) const
{
	return Rectf(m_Position.x, m_Position.y, m_SourceRect.width, m_SourceRect.height);
}
MovementDirection Ryu::GetMovementDirection( ) const
{
	return m_MovementDirection;
}

void Ryu::SetBorders(float posX)
{
	m_Position.x = posX;
}

void Ryu::ChangeMaxFramesOfAnimation()
{
	if (m_State == RyuState::none || m_State == RyuState::ducking || m_State == RyuState::hurt || m_State == RyuState::climbing)
	{
		m_MaxFramesOfAnimation = m_COLS_NOT_MOVING;
	}
	else if (m_State == RyuState::walking || m_State == RyuState::attacking || m_State == RyuState::duckAttacking)
	{
		m_MaxFramesOfAnimation = m_COLS_MOVING;
	}
	else if (m_State == RyuState::jumping)
	{
		m_MaxFramesOfAnimation = m_COLS_JUMPING;
	}
	
}

void Ryu::ChangeFrames(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FrameTime)
	{
		m_AccuSec-= m_FrameTime;

		++m_FrameNr;

		if (m_FrameNr >= m_MaxFramesOfAnimation)
		{
			if (m_State == RyuState::attacking) m_State = RyuState::walking;
			if (m_State == RyuState::duckAttacking) m_State = RyuState::ducking;
			m_FrameNr = 0;
		}
	}
	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking) && m_FrameNr > 0)
	{
		if (!m_IsAttacking)
		{
			m_KatanaPtr->SetIsActive(true);
		}
		m_IsAttacking = true;
		m_KatanaPtr->ChangeFrames(m_FrameNr - 1);
	}
	else
	{
		m_IsAttacking = false;
		m_KatanaPtr->SetIsActive(false);
	}
}


void Ryu::ChangePosition(float elapsedSec)
{

	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;


	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking))
	{
		if (m_FrameNr == 1)
		{
			if (m_MovementDirection == MovementDirection::right)
			{
				m_KatanaPtr->ChangePosition(Point2f(m_Position.x + m_SourceRect.width * m_SCALE * 1.f,
										                 m_Position.y + m_SourceRect.height * m_SCALE * 3.f / 5.f));	
			} else if (m_MovementDirection == MovementDirection::left)
			{
				m_KatanaPtr->ChangePosition(Point2f(m_Position.x ,
													 m_Position.y + m_SourceRect.height * m_SCALE * 3.f / 5.f));	
			}
			
		}
		else 
		{
			//m_KatanaPtr->ChangePosition(Point2f(m_Position.x + m_SourceRect.width / 2.f, m_Position.y + m_SourceRect.height * m_SCALE - m_KatanaPtr->GetSourceRect().height + 10.f));
			if (m_MovementDirection == MovementDirection::right)
			{
				m_KatanaPtr->ChangePosition(Point2f(m_Position.x + m_SourceRect.width * m_SCALE * 0.7f,
														 m_Position.y + m_SourceRect.height * m_SCALE * 2.f / 3.f));	
			} else if (m_MovementDirection == MovementDirection::left)
			{
				m_KatanaPtr->ChangePosition(Point2f(m_Position.x + m_SourceRect.width * m_SCALE * 0.3f ,
													 m_Position.y + m_SourceRect.height * m_SCALE * 2.f / 3.f));	
			}
		}
	}
}

void Ryu::UpdateJump(float elapsedSec)
{
	m_Velocity.y -= 2500.f * (elapsedSec);
}