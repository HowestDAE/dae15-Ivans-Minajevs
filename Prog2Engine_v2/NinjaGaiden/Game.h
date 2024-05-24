#pragma once
#include <unordered_map>

#include "BaseGame.h"
#include <vector>

#include "CollectibleType.h"
#include "EnemyType.h"
#include "StageType.h"
#include "TextManager.h"
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
class CollectiblesManager;
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

	static const int m_INIT_HEALTH { 16 };
	
	std::unordered_map<std::string, EnemyType> m_ENEMY_TABLE {
				{"biker", EnemyType::biker},
				{"boxer",EnemyType::boxer},
				{"knifeMan",EnemyType::knifeMan},
				{"dog",EnemyType::dog},
				{"boss", EnemyType::boss}};
	std::unordered_map<std::string, CollectibleType> m_COLLECTIBLE_TABLE  {
				{ "bonusBlue", CollectibleType::bonusBlue},
				{ "bonusRed", CollectibleType::bonusRed},
				{ "spiritualStrengthBlue", CollectibleType::spiritualStrengthBlue},
				{ "spiritualStrengthRed", CollectibleType::spiritualStrengthRed},
				{ "timeFreeze", CollectibleType::timeFreeze},
				{ "throwingStar", CollectibleType::throwingStar},
				{ "windmillThrowingStar", CollectibleType::windmillThrowingStar},
				{ "theArtOfTheFireWheel", CollectibleType::theArtOfTheFireWheel},
				{ "invincibleFireWheel", CollectibleType::invincibleFireWheel},
				{ "jumpAndSlashTechnique", CollectibleType::jumpAndSlashTechnique},
				{ "none", CollectibleType::none}};

	const int m_FONT_SIZE { 24 };
private:
	
	float m_Timer { 150.f };
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
	CollectiblesManager* m_CollectiblesManagerPtr;
	TextManager* m_TextManagerPtr;
	
	std::vector<std::vector<Point2f>> m_FloorVertices;
	std::vector<std::vector<Point2f>> m_PlatformsVertices;
	std::vector<std::vector<Point2f>> m_SignsVertices;
	std::vector<std::vector<Point2f>> m_WallsVertices;

	StageType m_StageType { StageType::generalMap };

	int m_Score{ 0 };
	
	std::string m_Alphabet { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-" };
	std::vector<std::vector<std::vector<Point2f>>> m_MapVertices;

	
	// FUNCTIONS
	void DrawHealth(Point2f pos, const std::string& text, int health) const;
	void ReadEnemyDataFromFile(const std::string& filename) const;
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};