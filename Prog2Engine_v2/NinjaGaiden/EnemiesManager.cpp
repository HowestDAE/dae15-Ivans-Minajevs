#include "pch.h"
#include "EnemiesManager.h"
#include "Enemy.h"

void EnemiesManager::Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec)
{
	for (Enemy*& enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			enemyPtr->Update(mapVertices, elapsedSec);
			if (!enemyPtr->GetIsAlive())
			{
				delete enemyPtr;
				enemyPtr = nullptr;
			}
		}
	}
}

void EnemiesManager::Draw( ) const
{
	for (Enemy* enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			enemyPtr->Draw();
		}
	}
}

void EnemiesManager::Add( Enemy* enemyPtr )
{
	m_EnemiesPtrArr.push_back(enemyPtr);
}
std::vector<Enemy*>& EnemiesManager::GetEnemiesArray( )
{
	return m_EnemiesPtrArr;
}
