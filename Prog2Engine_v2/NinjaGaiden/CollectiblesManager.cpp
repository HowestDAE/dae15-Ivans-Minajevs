#include "pch.h"
#include "CollectiblesManager.h"

void CollectiblesManager::Update( float elapsedSec, const TexturesManager* texturesManagerPtr, Rectf sourceRect )
{
	
}
void CollectiblesManager::Draw( ) const
{
	for ( Collectible* lanternPtr : m_CollectiblesPtrArr)
	{
		if (lanternPtr != nullptr)
		{
			lanternPtr->Draw();
		}
	}
}
void CollectiblesManager::Add(  Collectible*  collectiblePtr )
{
	m_CollectiblesPtrArr.push_back(collectiblePtr);
}

void CollectiblesManager::DeleteCollectible( const Collectible* collectible )
{
	for (Collectible*& collectiblePtr : m_CollectiblesPtrArr)
	{
		if (collectiblePtr != nullptr && collectible != nullptr)
		{
			if (collectiblePtr ==  collectible)
			{
				delete collectiblePtr;
				collectiblePtr = nullptr;
			}
		}
	}
}

void CollectiblesManager::DeleteCollectibles( )
{
	for (Collectible*& lanternPtr : m_CollectiblesPtrArr)
	{
		if (lanternPtr != nullptr)
		{
			delete lanternPtr;
			lanternPtr = nullptr;
		}
	}
}
std::vector<Collectible*>& CollectiblesManager::GetCollectiblesArray( )
{
	return m_CollectiblesPtrArr;
}