#pragma once
#include "Collectible.h"

class Ryu;
class CollectiblesManager final
{
public:
	void Update(float elapsedSec, const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, Ryu* ryuPtr);
	void Draw() const;

	void Add(Collectible* collectiblePtr);

	void DeleteCollectible( const Collectible* collectible);

	void DeleteCollectibles();

	std::vector<Collectible*>& GetCollectiblesArray();

private:
	std::vector<Collectible*> m_CollectiblesPtrArr;
};
