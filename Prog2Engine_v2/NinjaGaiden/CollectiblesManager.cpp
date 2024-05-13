#include "pch.h"
#include "CollectiblesManager.h"

void CollectiblesManager::Update( float elapsedSec, const std::vector<std::vector<std::vector<Point2f>>>& mapVertices) 
{
	for ( Collectible*& collectiblePtr : m_CollectiblesPtrArr)
	{
		if (collectiblePtr != nullptr)
		{
			collectiblePtr->Update(mapVertices, elapsedSec);
			if (!collectiblePtr->GetIsExisting())
			{
				DeleteCollectible(collectiblePtr);
				collectiblePtr = nullptr;
			}
		}
	}
}
void CollectiblesManager::Draw( ) const
{
	for ( Collectible* collectiblePtr : m_CollectiblesPtrArr)
	{
		if (collectiblePtr != nullptr)
		{
			collectiblePtr->Draw();
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