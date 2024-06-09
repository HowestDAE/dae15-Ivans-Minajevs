#pragma once
#include "Texture.h"
#include <Vector2f.h>
#include <vector>

#include "EnemiesManager.h"
#include "Game.h"
#include "LanternsManager.h"
#include "MovementDirection.h"
#include "SoundEffect.h"
#include "TextureManager.h"
class Katana;
class Ryu final
{
public: 
	enum class RyuState { none, walking, attacking, ducking, duckAttacking, hurt, jumping, climbing };
	explicit Ryu(const TexturesManager* texturesManager, Point2f pos, ThrowingWeaponsManager* throwingWeaponsManagerPtr);
	explicit Ryu(const TexturesManager* texturesManager, float posX, float posY, ThrowingWeaponsManager* throwingWeaponsManagerPtr);
	~Ryu();

	Ryu(const Ryu&) = delete;
	Ryu& operator=(const Ryu&) = delete;
	Ryu(Ryu&&) = delete;
	Ryu& operator=(Ryu&&) = delete;

	//~Ryu();

	void Draw() const;
	void Update(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<std::vector<Point2f>>> &mapVertices, CollectiblesManager* collectiblesManagerPtr,
				EnemiesManager* enemiesManagerPtr, LanternsManager* lanternsManagerPtr);
	void HandleFloorCollision(const std::vector<std::vector<Point2f>>& vertices);
	void HandleSignsCollision(const std::vector<std::vector<Point2f>>& vertices);
	void HandlePlatformsCollision(const std::vector<std::vector<Point2f>>& vertices);
	void HandleWallsCollision(const std::vector<std::vector<Point2f>>& vertices);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	void AddCollectible(Collectible*& collectiblePtr);
	Collectible* GetOwnedCollectiblePtr() const;
	
	void ThrowingWeaponHit(Vector2f throwingWeaponVelocity);
	
	void ResetHealth();
	void SetPosition(Point2f pos);

	void IncreaseEnergy(int value);
	
	int GetHealth() const;
	void SetBorders(float posX);
	
	Point2f GetPosition() const;
	Rectf GetRect() const;
	MovementDirection GetMovementDirection() const;
	int GetEnergy() const;

	static const int m_ROWS;
	static const int m_COLS;

	static const int m_COLS_MOVING;
	static const int m_COLS_NOT_MOVING;
	static const int m_COLS_JUMPING;

	static const float	 m_FRAME_WIDTH;
	static const float  m_FRAME_HEIGHT;

	static const float m_SPEED;
	static const float m_INIT_JUMP_SPEED;
	
	static const float m_SCALE;

private:
	MovementDirection m_MovementDirection;
	MovementDirection m_PlannedJumpDirection;

	RyuState m_State;
	
	int m_Health { Game::m_INIT_HEALTH};
	
	bool m_IsMoving;
	bool m_IsAttacking { false };

	Texture* m_RyuSpriteSheetPtr;
	Rectf m_SourceRect;

	Point2f m_Position;
	Katana* m_KatanaPtr;

	Collectible* m_CollectiblePtr { nullptr };
	ThrowingWeaponsManager* m_ThrowingWeaponsManagerPtr;

	SoundEffect* m_AttackSound;
	SoundEffect* m_JumpSound;
	SoundEffect* m_HitSound;
	SoundEffect* m_CollectibleTake;
	
	Vector2f m_Velocity;
	//float m_Acceleration;
	//float m_VerticalPosBeforeJump;

	float m_AccuSec;
	int	  m_FramesPerSec;
	float m_FrameTime;
	
	int m_FrameNr;
	int	m_MaxFramesOfAnimation;

	//float m_TimeResistentAfterHit { 1.5f };

	int m_Energy{ 0 };
	int m_JumpActionsCounter;
	int m_AttackActionCounter;

	bool m_IsThrowing{ false };
	void InitializeSourceRect();
	void UpdateSourceRect();
	void ChangeMaxFramesOfAnimation();
	void ChangeFrames(float elapsedSec);
	void ChangePosition(float elapsedSec);
	void UpdateJump(float elapsedSec);
	void ChangeDirection(MovementDirection direction);


	void EnemyHit(const Enemy* enemyPtr);
};

