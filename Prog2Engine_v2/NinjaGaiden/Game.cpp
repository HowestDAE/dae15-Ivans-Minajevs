#include "pch.h"
#include "Game.h"
#include <fstream>
#include <iomanip>

#include "Ryu.h"
#include "Camera.h"
#include "SvgParser.h"
#include "SoundStream.h"
#include "ParticlesManager.h"
#include <iostream>
#include "Biker.h"
#include "Boss.h"
#include "Boxer.h"
#include "CollectibleTrigger.h"
#include "Dog.h"
#include "EnemiesManager.h"
#include "Enemy.h"
#include "EnemyTrigger.h"
#include "KnifeMan.h"
#include "LanternsManager.h"
#include "SoundEffectsManager.h"
#include "TextureManager.h"
#include "TriggersManager.h"
#include "utils.h"

const int Game::m_FONT_SIZE{ 24 };
const float Game::m_MAP_SCALE{ 3.f };
const int Game::m_INIT_HEALTH { 16 };
Game::Game( const Window& window )
	: BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{

	m_BackgroundMusicPtr = new SoundStream("background_music.mp3");

	m_ParticlesManagerPtr = new ParticlesManager();
	m_TexturesManagerPtr = new TexturesManager();
	m_SoundEffectsManagerPtr = new SoundEffectsManager();
	m_EnemiesManagerPtr = new EnemiesManager();
	m_TriggersManagerPtr = new TriggersManager();
	m_LanternsManagerPtr = new LanternsManager();
	m_CollectiblesManagerPtr = new CollectiblesManager();
	m_ThrowingWeaponsManager = new ThrowingWeaponsManager();

	ReadEnemyDataFromFile("enemies_triggers.txt");

	m_TexturesManagerPtr->AddTexture(TextureType::ryu, "ryu_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::katana, "katana_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::map, "ninja_gaiden_map_stage_1_8bit.png");
	m_TexturesManagerPtr->AddTexture(TextureType::particles, "death_particle.png");
	m_TexturesManagerPtr->AddTexture(TextureType::enemies, "enemies_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::collectibles, "collectibles_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::boss, "boss_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::bossMap, "ninja_gaiden_map_stage_boss_8bit.png");
	m_TexturesManagerPtr->AddTexture(TextureType::throwingWeapon, "weapons_spritesheet.png");
	m_TexturesManagerPtr->AddText(TextureType::text, m_Alphabet, "ninja_gaiden_nes.ttf", m_FONT_SIZE, Color4f(1.f, 1.f, 1.f, 1.f));

	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::attack, R"(sound_effects\attack.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::jump, R"(sound_effects\jump.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::ryuHit, R"(sound_effects\ryu_hit.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::enemyDeath, R"(sound_effects\enemy_death.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::bossDeath, R"(sound_effects\boss_death.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::collectibleTake, R"(sound_effects\collectibles.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::gameOver, R"(sound_effects\game_over.wav)");
	m_SoundEffectsManagerPtr->AddSoundEffect(SoundEffectType::bossDeathMy, R"(sound_effects\boss_death_my.wav)");
	
	m_DeathStageSound = m_SoundEffectsManagerPtr->GetSoundEffect(SoundEffectType::gameOver);
	m_TextManagerPtr = new TextManager(m_Alphabet);


	
	//m_LanternsManagerPtr->Add(new Lantern(Point2f(900.f, 160.f), CollectibleType::BonusBlue, m_TexturesManagerPtr));

	m_TriggersManagerPtr->AddTrigger(new CollectibleTrigger(Point2f(900.f, 160.f), CollectibleType::bonusBlue ));

	//100.f * m_MAP_SCALE
	m_RyuPtr = new Ryu(TexturesManager::GetInstance(), 100.f, 70.f, m_ThrowingWeaponsManager);
	m_MapTexturePtr = m_TexturesManagerPtr->GetTexture(TextureType::map);
	m_Camera = new Camera(GetViewPort().width, GetViewPort().height);
	
	SVGParser::GetVerticesFromSvgFile("map_floor.svg", m_FloorVertices);
	SVGParser::GetVerticesFromSvgFile("map_platforms.svg", m_PlatformsVertices);
	SVGParser::GetVerticesFromSvgFile("map_signs.svg", m_SignsVertices);
	SVGParser::GetVerticesFromSvgFile("map_walls.svg", m_WallsVertices);

	m_MapVertices.push_back(m_FloorVertices);
	m_MapVertices.push_back(m_PlatformsVertices);
	m_MapVertices.push_back(m_SignsVertices);
	m_MapVertices.push_back(m_WallsVertices);

	for (std::vector<std::vector<Point2f>>& verticesType : m_MapVertices)
	{
		for (std::vector<Point2f>& vertices : verticesType)
		{
			for (Point2f &point : vertices)
			{
				point.x = int(point.x) * m_MAP_SCALE;
				point.y = int(point.y) * m_MAP_SCALE;
			}
		}
	}
}


void Game::ReadEnemyDataFromFile(const std::string& filename) const
{
	std::vector<Enemy> enemies;
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << '\n';
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string token;

		TriggerType triggerType;
		if (std::getline(iss, token, ','))
		{
			if (token == "enemy")
			{
				triggerType = TriggerType::enemy;
			} else if (token == "collectible")
			{
				triggerType = TriggerType::collectible;
			}
		}
		// Retrive position
		float posX;
		if (std::getline(iss, token, ',')) {
			posX = std::stof(token);
		} else {
			std::cerr << "Invalid file format: position missing" << '\n';
			continue;
		}

		float posY;
		if (std::getline(iss, token, ',')) {
			posY = std::stof(token);
		} else {
			std::cerr << "Invalid file format: position missing" << '\n';
			continue;
		}

		// Read type
		if ( triggerType == TriggerType::enemy )
		{
			EnemyType enemyType;
			if (std::getline(iss, token, ',')) {
				auto it = m_ENEMY_TABLE.find(token);
				if (it != m_ENEMY_TABLE.end()) {
					enemyType = it->second;
				} else {
					std::cout << "Enemy type not found!" << '\n';
				}
			} else {
				std::cerr << "Invalid file format: type missing" << '\n';
				continue;
			}

			// Read direction
			MovementDirection direction;
			if (std::getline(iss, token, ',')) {
				if (token == "left")
				{
					direction = MovementDirection::left;
				} else if (token == "right")
				{
					direction = MovementDirection::right;
				}
			} else {
				std::cerr << "Invalid file format: direction missing" << '\n';
				continue;
			}
			//std::cout << posX << " " << posY << " " << static_cast<int>(enemyType) << " " <<  static_cast<int>(direction) << "\n";
			m_TriggersManagerPtr->AddTrigger(new EnemyTrigger(Point2f(posX, posY), enemyType, direction));
		} else if (triggerType == TriggerType::collectible)
		{
			CollectibleType collectibleType;
			if (std::getline(iss, token, ',')) {
				auto it = m_COLLECTIBLE_TABLE.find(token);
				if (it != m_COLLECTIBLE_TABLE.end()) {
					collectibleType = it->second;
				} else {
					std::cout << "Enemy type not found!" << '\n';
				}
			} else {
				std::cerr << "Invalid file format: type missing" << '\n';
				continue;
			}
			m_TriggersManagerPtr->AddTrigger(new CollectibleTrigger(Point2f(posX, posY), collectibleType));
		}
	} 
}

void Game::Cleanup( )
{
	delete m_RyuPtr;
	m_RyuPtr = nullptr;

	delete m_Camera;
	m_Camera = nullptr;

	delete m_BackgroundMusicPtr;
	m_BackgroundMusicPtr = nullptr;

	delete m_TextManagerPtr;

	m_SoundEffectsManagerPtr->DeleteSoundEffects();
	m_TexturesManagerPtr->DeleteTextures();
	m_EnemiesManagerPtr->DeleteEnemies();
	m_TriggersManagerPtr->DeleteTriggers();
	m_ParticlesManagerPtr->DeleteParticles();
	m_LanternsManagerPtr->DeleteLanterns();
	m_CollectiblesManagerPtr->DeleteCollectibles();
	m_ThrowingWeaponsManager->DeleteWeapons();
	
	delete m_SoundEffectsManagerPtr;
	delete m_LanternsManagerPtr;
	delete m_TexturesManagerPtr;
	delete m_ParticlesManagerPtr;
	delete m_EnemiesManagerPtr;
	delete m_TriggersManagerPtr;
	delete m_CollectiblesManagerPtr;
	delete m_ThrowingWeaponsManager;
	
}

void Game::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_RyuPtr->Update(elapsedSec, pStates, m_MapVertices, m_CollectiblesManagerPtr, m_EnemiesManagerPtr, m_LanternsManagerPtr);

	if (m_RyuPtr->GetPosition().x + m_RyuPtr->GetRect().width > m_MapTexturePtr->GetWidth() * m_MAP_SCALE - 60.f && m_StageType == StageType::generalMap)
	{
		m_MapTexturePtr = m_TexturesManagerPtr->GetTexture(TextureType::bossMap);
		m_RyuPtr->SetPosition(Point2f(100.f, 70.f));
		m_StageType = StageType::bossRoom;
	}

	bool isEnemyCopyFound{ false };
		bool isCollectibleCopyFound{ false };
		
		for (Trigger* triggerPtr : m_TriggersManagerPtr->GetTriggersArray())
		{
			if (triggerPtr != nullptr)
			{
				if (triggerPtr->GetIsActivated())
				{
					if (triggerPtr->GetTriggerType() == TriggerType::enemy)
					{
						for (Enemy* enemyPtr : m_EnemiesManagerPtr->GetEnemiesArray())
						{
							if (enemyPtr != nullptr)
							{
								if (enemyPtr->GetTriggerPointer() == triggerPtr)
								{
									isEnemyCopyFound = true;
									break;
								}
							}
						}
						if (!isEnemyCopyFound)
						{
							switch (triggerPtr->GetEnemyType())
							{
							case EnemyType::biker:
								m_EnemiesManagerPtr->Add(new Biker(m_TexturesManagerPtr, triggerPtr, 50.f));
								break;
							case EnemyType::boxer:
								m_EnemiesManagerPtr->Add(new Boxer(m_TexturesManagerPtr, triggerPtr, 40.f));
								break;
							case EnemyType::dog:
								m_EnemiesManagerPtr->Add(new Dog(m_TexturesManagerPtr, triggerPtr, 400.f));
								break;
							case EnemyType::knifeMan:
								m_EnemiesManagerPtr->Add(new KnifeMan(m_TexturesManagerPtr, triggerPtr, 30.f, m_ThrowingWeaponsManager));
								break;
							case EnemyType::boss:
								if (m_StageType == StageType::bossRoom)
								{
									m_EnemiesManagerPtr->Add(new Boss(m_TexturesManagerPtr, triggerPtr, 30.f));
									m_TriggersManagerPtr->DeleteTrigger(triggerPtr);
								}
								break;	
							case EnemyType::none:
								break;
							}
						}
					}
					if (triggerPtr->GetTriggerType() == TriggerType::collectible)
					{
						for (Lantern* lanternPtr : m_LanternsManagerPtr->GetLanternsArray())
						{
							if (lanternPtr != nullptr)
							{
								if (lanternPtr->GetTriggerPointer() == triggerPtr)
								{
									isCollectibleCopyFound = true;
									break;
								}

							}
						}
						if (!isCollectibleCopyFound)
						{
							if (triggerPtr->GetIsAvailable())
							{
								m_LanternsManagerPtr->Add(new Lantern(triggerPtr->GetPosition(), triggerPtr->GetCollectibleType(), triggerPtr, m_TexturesManagerPtr));
							}
						}
					}
				}
			}
		}

	
	if (m_RyuPtr->GetPosition().x < 5.f) m_RyuPtr->SetBorders(5.f);
	if (m_RyuPtr->GetPosition().x > m_MapTexturePtr->GetWidth() * m_MAP_SCALE - m_RyuPtr->GetRect().width)
	{
		m_RyuPtr->SetBorders(m_MapTexturePtr->GetWidth() * m_MAP_SCALE - m_RyuPtr->GetRect().width);
	}


	if (m_StageType == StageType::bossRoom)
	{
		const Rectf srcRect { Rectf(0.f, 0.f, m_MapTexturePtr->GetWidth() * m_MAP_SCALE,  m_MapTexturePtr->GetHeight() * m_MAP_SCALE)};
		m_TriggersManagerPtr->UpdateTrigger( srcRect, m_RyuPtr->GetMovementDirection());
		m_EnemiesManagerPtr->Update(m_MapVertices, elapsedSec, m_ParticlesManagerPtr, m_TexturesManagerPtr,  srcRect, m_BackgroundMusicPtr);
		m_ParticlesManagerPtr->Update(elapsedSec);
		m_CollectiblesManagerPtr->Update(elapsedSec, m_MapVertices, m_RyuPtr);
		m_ThrowingWeaponsManager->Update(elapsedSec, srcRect, m_RyuPtr, m_EnemiesManagerPtr);
	}
	if (m_StageType == StageType::generalMap)
	{
		m_Timer -= elapsedSec;

		m_Camera->Update(m_MapTexturePtr->GetWidth() * m_MAP_SCALE, m_MapTexturePtr->GetHeight() * m_MAP_SCALE, m_RyuPtr->GetPosition());
		m_TriggersManagerPtr->UpdateTrigger(m_Camera->GetViewRect(), m_RyuPtr->GetMovementDirection());

		m_EnemiesManagerPtr->Update(m_MapVertices, elapsedSec, m_ParticlesManagerPtr, m_TexturesManagerPtr,  m_Camera->GetViewRect(), m_BackgroundMusicPtr);
		m_LanternsManagerPtr->Update(elapsedSec, m_TexturesManagerPtr, m_Camera->GetViewRect());

		m_CollectiblesManagerPtr->Update(elapsedSec, m_MapVertices, m_RyuPtr);

		m_ThrowingWeaponsManager->Update(elapsedSec, m_Camera->GetViewRect(), m_RyuPtr, m_EnemiesManagerPtr);
		m_ParticlesManagerPtr->Update(elapsedSec);

	
		if (!m_BackgroundMusicPtr->IsPlaying())
		{
			m_BackgroundMusicPtr->Play(true);
			m_BackgroundMusicPtr->Resume();
		}
	}
	

	

	m_Score = m_EnemiesManagerPtr->GetScore();

	if (m_StageType != StageType::dead)
	{
		if (((m_RyuPtr->GetHealth() == 0 || Boss::GetHealth() == 0 )) || m_Timer < 0)
		{
			bool isParticlesManagerEmpty { true };
			for (Particle* particlePtr : m_ParticlesManagerPtr->GetParticlesArray())
			{
				if (particlePtr != nullptr)
				{
					isParticlesManagerEmpty = false;
				}
			}
			if (isParticlesManagerEmpty)
			{
				m_BackgroundMusicPtr->Pause();
				m_StageType = StageType::dead;
				m_RyuPtr->DeleteOwnedCollectible(m_CollectiblesManagerPtr);
				m_EnemiesManagerPtr->DeleteEnemies();
				m_ParticlesManagerPtr->DeleteParticles();
				m_LanternsManagerPtr->DeleteLanterns();
				m_CollectiblesManagerPtr->DeleteCollectibles();
				m_ThrowingWeaponsManager->DeleteWeapons();
				m_DeathStageSound->Play(0);
			}
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	if (m_StageType != StageType::dead)
	{
		glPushMatrix();
		{
			if (m_StageType == StageType::bossRoom)
			{
				glTranslatef((GetViewPort().width - m_MapTexturePtr->GetWidth() * m_MAP_SCALE) / 2.f, 0.f, 0.f);
			}
			glScalef(m_MAP_SCALE, m_MAP_SCALE, 1.f);
		
		

			m_MapTexturePtr->Draw();
		}
		glPopMatrix();

		m_LanternsManagerPtr->Draw();

		m_CollectiblesManagerPtr->Draw();
	
		m_RyuPtr->Draw();
	
		m_EnemiesManagerPtr->Draw();

		m_ThrowingWeaponsManager->Draw();
		
		m_ParticlesManagerPtr->Draw();
	
		m_Camera->Reset();

		m_TextManagerPtr->Draw(Point2f(50.f, GetViewPort().height- 70.f),std::string("TIMER-" + std::to_string(int(m_Timer))));
	
		std::ostringstream score;
		score << std::setw(6) << std::setfill('0') << m_Score;
	
		m_TextManagerPtr->Draw(Point2f(50.f, GetViewPort().height- 40.f),std::string("SCORE-" + score.str()));

		m_TextManagerPtr->Draw(Point2f(GetViewPort().width / 2.f + 20.f, GetViewPort().height- 40.f),std::string("STAGE-1-" + std::to_string(static_cast<int>(m_StageType))));

		m_TextManagerPtr->Draw(Point2f(50.f, GetViewPort().height- 100.f),std::string("P-02"));

		std::ostringstream energy;
		energy << std::setw(2) << std::setfill('0') << m_RyuPtr->GetEnergy();
	
		m_TextManagerPtr->Draw(Point2f(200.f, GetViewPort().height-  100.f),std::string(energy.str()));

		m_TextManagerPtr->Draw(Point2f(50.f, GetViewPort().height- 40.f),std::string("SCORE-" + score.str()));
		
		DrawHealth(Point2f(GetViewPort().width / 2.f + 20.f, GetViewPort().height- 70.f),std::string("NINJA-"), m_RyuPtr->GetHealth());
		DrawHealth(Point2f(GetViewPort().width / 2.f + 20.f, GetViewPort().height- 100.f),std::string("ENEMY-"), Boss::GetHealth());
		

		utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
		utils::DrawRect(Point2f(298.f, GetViewPort().height- 100.f), 41.f, 40.f, 3.f);
	
		utils::SetColor(Color4f(1.f, 0.5f, 0.7f, 1.f));

		Collectible* collectiblePtr = m_RyuPtr->GetOwnedCollectiblePtr();
		if (collectiblePtr != nullptr)
		{
			collectiblePtr->SetPosition(Point2f(300.f, GetViewPort().height- 100.f));
			collectiblePtr->Draw();
		}
	}
	else
	{
		m_Camera->Reset();
		m_TextManagerPtr->Draw(Point2f(200.f, GetViewPort().height / 2.f),std::string("PRESS R TO RESTART"));
		
	}

	
	
}

void Game::DrawHealth( Point2f pos, const std::string& text,  int health) const
{
	m_TextManagerPtr->Draw(pos,text);
	utils::SetColor(Color4f(1.f, 0.5f, 0.7f, 1.f));
	
	float posX { pos.x + text.length() * m_FONT_SIZE };
	float width { 10.f };
	
	for (int healthIndex { 0 }; healthIndex < health; ++healthIndex)
	{
		utils::FillRect(posX, pos.y, width, float(m_FONT_SIZE));
		posX += (width + 5.f);
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_RyuPtr->ProcessKeyDownEvent(e);
	if (m_StageType == StageType::dead)
	{
		if (e.keysym.sym == SDLK_r)
		{
			m_StageType = StageType::generalMap;
			m_MapTexturePtr = m_TexturesManagerPtr->GetTexture(TextureType::map);
			m_RyuPtr->SetPosition(Point2f(100.f, 70.f ));
			m_Timer =  150.f;
			m_RyuPtr->ResetHealth();
			Boss::ResetHealth();
			m_BackgroundMusicPtr->Play(true);
			m_EnemiesManagerPtr->AddScore(-m_Score);
		}
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_RyuPtr->ProcessKeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

	//if (m_TestingDotPtr != nullptr)
	//{
	//	m_TestingDotPtr-> ProcessMouseDownEvent(e);
	//}
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
