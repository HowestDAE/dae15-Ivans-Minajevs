#pragma once
#include <vector>

#include "CollectibleType.h"
#include "TextureManager.h"

class Collectible
{
public:
	Collectible(Point2f position, CollectibleType type, const TexturesManager* texturesManagerPtr);
	void Draw() const;

	virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec);
    
	void HandleVerticalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices);

	void UpdateJump();
	
private:
	Point2f m_Position;
	CollectibleType m_Type;
	const TexturesManager* m_TexturesManagerPtr;
	
	bool isCollected;
	bool isExisting;
	
};
