#pragma once
#include <vector>

#include "CollectiblesManager.h"
#include "Lantern.h"
#include "TextureManager.h"

class LanternsManager final
{
public:
	void Update(float elapsedSec, const TexturesManager* texturesManagerPtr, Rectf sourceRect);
	void Draw() const;

	void Add(Lantern* lanternPtr);

	void DeleteLantern( const Lantern* lantern);

	void DeleteLanterns();

	std::vector<Lantern*>& GetLanternsArray();

private:
	std::vector<Lantern*> m_LanternsPtrArr;
};
