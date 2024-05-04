#pragma once
#include <Texture.h>
#include "Ryu.h"
#include "Enemy.h"
class Katana final
{
public:

	explicit Katana( const TexturesManager* texturesManager, Point2f pos);
	//Katana& operator=(const Katana& rhs);
	//Katana(const Katana& other);

	void Draw(MovementDirection state) const;
	void ChangePosition(Point2f pos);

	void Update( std::vector<Enemy*>& enemyArrPtr) const;

	Rectf GetSourceRect();

	void InitializeSourceRect();
	void UpdateSourceRect();
	void ChangeFrames(int frameNr);

	void SetIsActive(bool isActive);
	void CheckEnemiesHit(std::vector<Enemy*>& enemyArrPtr) const;

	//~Katana();

	const int m_MAX_FRAMES_OF_ANIMATION{ 2 };
	const float m_SCALE{ 0.5 };
	//const std::string m_FILE_NAME{ "katana_spritesheet.png" };
	
private:
	bool m_IsActive;
	Point2f m_Position;
	int m_FrameNr;
	Texture* m_KatanaSpriteSheetPtr;
	Rectf m_SourceRect;
};

