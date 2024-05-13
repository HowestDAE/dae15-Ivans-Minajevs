#pragma once
#include <vector>

#include "CollectibleType.h"
#include "TextureManager.h"

class Collectible
{
public:
	Collectible(Point2f position, CollectibleType type);
	void Draw() const;

	virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec);
    
	void HandleVerticalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices);

	void UpdateJump(float elapsedSec);

	void UpdateSourceRect( );

	bool GetIsExisting() const;
	void SetIsExisting(bool isExisting);
	void SetIsCollected(bool isCollected);

	Rectf GetRect() const;
	
	const float m_SCALE{ 2.5f };

	const int m_COLS { 10 };
	const int m_ROWS { 2 };

protected:
	int m_FrameNr { 0 };
private:
	Point2f m_Position;
	Point2f m_Velocity;
	CollectibleType m_Type;
	Rectf m_SourceRect;

	Texture* m_CollectibleTexturePtr;
	
	bool m_IsCollected { false };
	bool m_IsExisting { true };

	float m_TimeAlive;
};
