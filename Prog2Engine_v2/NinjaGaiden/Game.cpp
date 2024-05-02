#include "pch.h"
#include "Game.h"
#include "Ryu.h"
#include "Camera.h"
#include "SvgParser.h"
#include "SoundStream.h"
#include "TestingDot.h"
#include "ParticlesManager.h"
#include "ParticleType.h"
#include <iostream>
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
	m_TestingDotPtr = new TestingDot(Point2f(500.f, 150.f), 20.f);
	m_BackgroundMusicPtr = new SoundStream("background_music.mp3");

	m_ParticlesManagerPtr = new ParticlesManager();

	m_RyuPtr = new Ryu(80.f, 70.f);
	m_MapTexturePtr = new Texture("ninja_gaiden_map_stage_1_8bit.png");
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

void Game::Cleanup( )
{
	delete m_RyuPtr;
	m_RyuPtr = nullptr;

	delete m_MapTexturePtr;
	m_MapTexturePtr = nullptr;

	delete m_Camera;
	m_Camera = nullptr;

	delete m_BackgroundMusicPtr;
	m_BackgroundMusicPtr = nullptr;

	delete m_TestingDotPtr;
	m_TestingDotPtr = nullptr;
}

void Game::Update(float elapsedSec)
{
	if (m_TestingDotPtr != nullptr)
	{
		if (!m_TestingDotPtr->GetIsAlive())
		{
			m_ParticlesManagerPtr->Add(ParticleType::enemyDeath, m_TestingDotPtr->GetPosition(), 0.5f);
			delete m_TestingDotPtr;
			m_TestingDotPtr = nullptr;
		}
	}
	m_ParticlesManagerPtr->Update(elapsedSec);
	if (!m_BackgroundMusicPtr->IsPlaying())
	{
		m_BackgroundMusicPtr->Play(true);
	}
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_RyuPtr->Update(elapsedSec, pStates, m_MapVertices);
	if (m_RyuPtr->GetPosition().x < 5.f) m_RyuPtr->SetBorders(5.f);
	if (m_RyuPtr->GetPosition().x > m_MapTexturePtr->GetWidth() * m_MAP_SCALE - 5.f) m_RyuPtr->SetBorders(m_MapTexturePtr->GetWidth() * m_MAP_SCALE - 5.f);
}

void Game::Draw( ) const
{
	ClearBackground( );

	
	m_Camera->Aim(m_MapTexturePtr->GetWidth() * m_MAP_SCALE, m_MapTexturePtr->GetHeight() * m_MAP_SCALE, m_RyuPtr->GetPosition());
	glPushMatrix();
	{
		glScalef(m_MAP_SCALE, m_MAP_SCALE, 1.f);

		m_MapTexturePtr->Draw();
	}
	glPopMatrix();
	
	m_RyuPtr->Draw();
	
	utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));

	for (const std::vector<std::vector<Point2f>>& verticesType : m_MapVertices)
	{
		for (const std::vector<Point2f>& vertices : verticesType)
		{
			utils::DrawPolygon(vertices, true, 2.f);
		}
	}

	if (m_TestingDotPtr != nullptr)
	{
		m_TestingDotPtr->Draw();
	}
	
	m_ParticlesManagerPtr->Draw();


	m_Camera->Reset();

	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_RyuPtr->ProcessKeyDownEvent(e);
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

	if (m_TestingDotPtr != nullptr)
	{
		m_TestingDotPtr-> ProcessMouseDownEvent(e);
	}
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
