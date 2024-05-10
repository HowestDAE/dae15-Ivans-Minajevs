#pragma once
#include <unordered_map>

#include "BaseGame.h"
#include <vector>

#include "CollectibleType.h"
#include "EnemyType.h"
#include "Texture.h"
class LanternsManager;
class TriggersManager;
class EnemiesManager;
class SvgParser;
class Camera;
class Ryu;
class TestingDot;
class SoundStream;
class ParticlesManager;
class TexturesManager;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	
	const float m_MAP_SCALE{ 3.f };

	static std::unordered_map<std::string, EnemyType> const m_ENEMY_TABLE;
	static std::unordered_map<std::string, CollectibleType> const m_COLLECTIBLE_TABLE;
private:
	Ryu* m_RyuPtr;
	Texture* m_MapTexturePtr;
	Camera* m_Camera;
	//TestingDot* m_TestingDotPtr;
	TriggersManager* m_TriggersManagerPtr;
	SoundStream* m_BackgroundMusicPtr;
	ParticlesManager* m_ParticlesManagerPtr;
	TexturesManager* m_TexturesManagerPtr;
	EnemiesManager* m_EnemiesManagerPtr;
	LanternsManager* m_LanternsManagerPtr;

	std::vector<std::vector<Point2f>> m_FloorVertices;
	std::vector<std::vector<Point2f>> m_PlatformsVertices;
	std::vector<std::vector<Point2f>> m_SignsVertices;
	std::vector<std::vector<Point2f>> m_WallsVertices;

	std::vector<std::vector<std::vector<Point2f>>> m_MapVertices;

	
	// FUNCTIONS
	void ReadEnemyDataFromFile(const std::string& filename) const;
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};