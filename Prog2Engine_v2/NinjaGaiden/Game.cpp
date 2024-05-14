#include "pch.h"
#include "Game.h"
#include <fstream>
#include "Ryu.h"
#include "Camera.h"
#include "SvgParser.h"
#include "SoundStream.h"
#include "ParticlesManager.h"
#include <iostream>
#include "Biker.h"
#include "Boxer.h"
#include "Dog.h"
#include "EnemiesManager.h"
#include "Enemy.h"
#include "KnifeMan.h"
#include "LanternsManager.h"
#include "TextureManager.h"
#include "TriggersManager.h"
#include "utils.h"



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
	m_EnemiesManagerPtr = new EnemiesManager();
	m_TriggersManagerPtr = new TriggersManager();
	m_LanternsManagerPtr = new LanternsManager();
	m_CollectiblesManagerPtr = new CollectiblesManager();

	ReadEnemyDataFromFile("enemies_triggers.txt");

	m_TexturesManagerPtr->AddTexture(TextureType::ryu, "ryu_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::katana, "katana_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::map, "ninja_gaiden_map_stage_1_8bit.png");
	m_TexturesManagerPtr->AddTexture(TextureType::particles, "death_particle.png");
	m_TexturesManagerPtr->AddTexture(TextureType::enemies, "enemies_spritesheet.png");
	m_TexturesManagerPtr->AddTexture(TextureType::collectibles, "collectibles_spritesheet.png");
	m_TexturesManagerPtr->AddText(TextureType::text, m_Alphabet, "ninja_gaiden_nes.ttf", 24, Color4f(1.f, 1.f, 1.f, 1.f));

	m_TextManagerPtr = new TextManager(m_Alphabet);

	//m_LanternsManagerPtr->Add(new Lantern(Point2f(900.f, 160.f), CollectibleType::BonusBlue, m_TexturesManagerPtr));

	m_TriggersManagerPtr->AddTrigger(new CollectibleTrigger(Point2f(900.f, 160.f), CollectibleType::bonusBlue ));
	
	m_RyuPtr = new Ryu(TexturesManager::GetInstance(), 100.f, 70.f);
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
				std::cout << point.x << " " << point.y << std::endl;
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
		if (std::getline(iss, token, ',')) {
			if (token == "enemy")
			{
				 triggerType = TriggerType::enemy;
			} else if (token == "collectible")
			{
				triggerType = TriggerType::collectible;
			}
		} else {
			std::cerr << "Invalid file format: direction missing" << '\n';
			continue;
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
	file.close();
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
	
	m_TexturesManagerPtr->DeleteTextures();
	m_EnemiesManagerPtr->DeleteEnemies();
	m_TriggersManagerPtr->DeleteTriggers();
	m_ParticlesManagerPtr->DeleteParticles();
	m_LanternsManagerPtr->DeleteLanterns();
	m_CollectiblesManagerPtr->DeleteCollectibles();

	
	delete m_LanternsManagerPtr;
	delete m_TexturesManagerPtr;
	delete m_ParticlesManagerPtr;
	delete m_EnemiesManagerPtr;
	delete m_TriggersManagerPtr;
	delete m_CollectiblesManagerPtr;
	
}

void Game::Update(float elapsedSec)
{
	m_Timer -= elapsedSec;
	
	bool isEnemyCopyFound { false };
	bool isCollectibleCopyFound { false };
	
	for (Trigger* triggerPtr: m_TriggersManagerPtr->GetTriggersArray())
	{
		if (triggerPtr != nullptr)
		{
			if (triggerPtr->GetIsActivated())
			{
				if(triggerPtr->GetTriggerType() == TriggerType::enemy)
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
							m_EnemiesManagerPtr->Add(new Biker(m_RyuPtr, m_TexturesManagerPtr, triggerPtr, 50.f));
							break;
						case EnemyType::boxer:
							m_EnemiesManagerPtr->Add(new Boxer(m_RyuPtr, m_TexturesManagerPtr, triggerPtr, 40.f));
							break;
						case EnemyType::dog:
							m_EnemiesManagerPtr->Add(new Dog(m_RyuPtr, m_TexturesManagerPtr, triggerPtr, 400.f));
							break;
						case EnemyType::knifeMan:
							m_EnemiesManagerPtr->Add(new KnifeMan(m_RyuPtr, m_TexturesManagerPtr, triggerPtr, 30.f));
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

	
	m_EnemiesManagerPtr->Update(m_MapVertices, elapsedSec, m_ParticlesManagerPtr, m_TexturesManagerPtr, m_Camera->GetViewRect());

	m_LanternsManagerPtr->Update(elapsedSec, m_TexturesManagerPtr, m_Camera->GetViewRect());

	m_CollectiblesManagerPtr->Update(elapsedSec, m_MapVertices);
	
	m_ParticlesManagerPtr->Update(elapsedSec);
	
	if (!m_BackgroundMusicPtr->IsPlaying())
	{
		m_BackgroundMusicPtr->Play(true);
	}
	
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_RyuPtr->Update(elapsedSec, pStates, m_MapVertices, m_CollectiblesManagerPtr, m_EnemiesManagerPtr, m_LanternsManagerPtr);
	if (m_RyuPtr->GetPosition().x < 5.f) m_RyuPtr->SetBorders(5.f);
	if (m_RyuPtr->GetPosition().x > m_MapTexturePtr->GetWidth() * m_MAP_SCALE - 5.f) m_RyuPtr->SetBorders(m_MapTexturePtr->GetWidth() * m_MAP_SCALE - 5.f);

	m_Camera->Update(m_MapTexturePtr->GetWidth() * m_MAP_SCALE, m_MapTexturePtr->GetHeight() * m_MAP_SCALE, m_RyuPtr->GetPosition());
	m_TriggersManagerPtr->UpdateTrigger(m_Camera->GetViewRect(), m_RyuPtr->GetMovementDirection());
}

void Game::Draw( ) const
{
	ClearBackground( );

	
	glPushMatrix();
	{
		glScalef(m_MAP_SCALE, m_MAP_SCALE, 1.f);

		m_MapTexturePtr->Draw();
	}
	glPopMatrix();

	m_LanternsManagerPtr->Draw();

	m_CollectiblesManagerPtr->Draw();
	
	m_RyuPtr->Draw();
	
	m_EnemiesManagerPtr->Draw();
	
	m_ParticlesManagerPtr->Draw();
	
	m_Camera->Reset();

	m_TextManagerPtr->Draw(Point2f(50.f, GetViewPort().height- 100.f),std::string("TIMER - " + std::to_string(int(m_Timer))));
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_RyuPtr->ProcessKeyDownEvent(e);
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
