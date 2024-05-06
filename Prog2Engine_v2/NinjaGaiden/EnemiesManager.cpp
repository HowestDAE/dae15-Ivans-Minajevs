#include "pch.h"
#include "EnemiesManager.h"
#include "Enemy.h"
#include "utils.h"

void EnemiesManager::Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec,
							ParticlesManager* particlesManagerPtr, const TexturesManager* texturesManagerPtr, Rectf sourceRect)
{
	for (Enemy*& enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			enemyPtr->Update(mapVertices, elapsedSec);
			
			if (!utils::IsPointInRect(enemyPtr->GetPosition(), sourceRect))
			{
				enemyPtr->SetIsAlive(false);
			}
			
			if (!enemyPtr->GetIsAlive())
			{
				particlesManagerPtr->Add(texturesManagerPtr, ParticleType::enemyDeath,
									Point2f(enemyPtr->GetPosition().x + enemyPtr->GetSourceRect().width / 2.f,
										enemyPtr->GetPosition().y + enemyPtr->GetSourceRect().height / 2.f), 0.5f);
				DeleteEnemy(enemyPtr);
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
void EnemiesManager::DeleteEnemy( const Enemy* enemy )
{
	for (Enemy*& enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr && enemy != nullptr)
		{
			if (enemyPtr == enemy)
			{
				
				delete enemyPtr;
				enemyPtr = nullptr;
			}
		}
	}
}

void EnemiesManager::DeleteEnemies( )
{
	for (Enemy*& enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			delete enemyPtr;
			enemyPtr = nullptr;
		}
	}
}

std::vector<Enemy*>& EnemiesManager::GetEnemiesArray( )
{
	return m_EnemiesPtrArr;
}
