#pragma once
#include <Texture.h>
#include "Ryu.h"
#include "LanternsManager.h"
class Katana final
{
public:

	explicit Katana( const TexturesManager* texturesManager, Point2f pos);
	//Katana& operator=(const Katana& rhs);
	//Katana(const Katana& other);

	void Draw(MovementDirection state) const;
	void ChangePosition(Point2f pos);

	void Update( LanternsManager* lanternsManagerPtr, EnemiesManager* enemiesManagerPtr, MovementDirection state, CollectiblesManager* collectiblesManagerPtr);

	Rectf GetSourceRect() const;
	float GetScale() const;

	void InitializeSourceRect();
	void UpdateSourceRect();
	void ChangeFrames(int frameNr);

	void SetIsActive(bool isActive);
	bool GetIsActivated() const;
	void CheckEnemiesHit(Enemy* enemyPtr, Rectf sourceRect);
	void CheckLanternsHit(Lantern* lanternPtr,  Rectf sourceRect, CollectiblesManager* collectibleManagerPtr) const;

	//~Katana();

	static const int m_MAX_FRAMES_OF_ANIMATION;
	static const float m_SCALE;
	//const std::string m_FILE_NAME{ "katana_spritesheet.png" };
	
private:
	bool m_IsActive;
	Point2f m_Position;
	int m_FrameNr;
	Texture* m_KatanaSpriteSheetPtr;
	Rectf m_SourceRect;
};

