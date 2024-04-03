#include "pch.h"
#include "Game.h"
#include "Ryu.h"
#include "Camera.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_RyuPtr = new Ryu(100.f, 70.f);
	m_MapTexturePtr = new Texture("ninja_gaiden_map_stage_1.png");
	m_Camera = new Camera(GetViewPort().width, GetViewPort().height);
}

void Game::Cleanup( )
{
	delete m_RyuPtr;
	m_RyuPtr = nullptr;

	delete m_MapTexturePtr;
	m_MapTexturePtr = nullptr;

	delete m_Camera;
	m_Camera = nullptr;
}

void Game::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_RyuPtr->Update(elapsedSec, pStates);
	if (m_RyuPtr->GetPosition().x < 5.f) m_RyuPtr->SetBorders(5.f);
	if (m_RyuPtr->GetPosition().x > m_MapTexturePtr->GetWidth() - 5.f) m_RyuPtr->SetBorders(m_MapTexturePtr->GetWidth() - 5.f);
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
