#include "pch.h"
#include "ThrowingWeaponsManager.h"

#include "Boss.h"
#include "Enemy.h"
#include "ThrowingWeapon.h"
#include "utils.h"

void ThrowingWeaponsManager::Update( float elapsedSec, Rectf viewRect,  Ryu* ryuPtr, EnemiesManager* enemiesManagerPtr)
{
	for (ThrowingWeapon*& throwingWeaponPtr : m_ThrowingWeaponPtrArr)
	{
		if (throwingWeaponPtr != nullptr)
		{
			
			throwingWeaponPtr->Update(elapsedSec);
			
			if (!utils::IsOverlapping(throwingWeaponPtr->GetCollisionRect(), viewRect))
			{
				DeleteWeapon(throwingWeaponPtr);
				break;
			}
			if (utils::IsOverlapping(throwingWeaponPtr->GetCollisionRect(), ryuPtr->GetRect()) && !throwingWeaponPtr->GetIsFriendly())
			{
				ryuPtr->ThrowingWeaponHit(throwingWeaponPtr->GetThrowingWeaponVelocity());
				DeleteWeapon(throwingWeaponPtr);
				break;
			}
			for (Enemy* enemyPtr : enemiesManagerPtr->GetEnemiesArray())
			{
				if (enemyPtr != nullptr)
				{
					if (utils::IsOverlapping(throwingWeaponPtr->GetCollisionRect(), enemyPtr->GetCollisionRect()) && throwingWeaponPtr->GetIsFriendly())
					{
						if (enemyPtr->GetTriggerPointer()->GetEnemyType() == EnemyType::boss)
						{
							Boss::Hit();
						}
						else
						{
							enemyPtr->SetIsAlive(false);
						}
						DeleteWeapon(throwingWeaponPtr);
						break;
					}
				}
			}
		}
		
	}
}
void ThrowingWeaponsManager::Draw( ) const
{
	for (ThrowingWeapon* throwingWeaponPtr : m_ThrowingWeaponPtrArr)
	{
		if (throwingWeaponPtr != nullptr)
		{
			throwingWeaponPtr->Draw();
		}
	}
}
void ThrowingWeaponsManager::Add( ThrowingWeaponType type, Point2f initPos, Vector2f initVelocity, bool isFriend)
{
	m_ThrowingWeaponPtrArr.push_back(new ThrowingWeapon(type, initPos, initVelocity, isFriend));
}
std::vector<ThrowingWeapon*>& ThrowingWeaponsManager::GetWeaponArray( )
{
	return  m_ThrowingWeaponPtrArr;
}

void ThrowingWeaponsManager::DeleteWeapon( const ThrowingWeapon* throwingWeapon )
{
	for (ThrowingWeapon*&  throwingWeaponPtr : m_ThrowingWeaponPtrArr)
	{
		if (throwingWeaponPtr != nullptr && throwingWeapon!= nullptr)
		{
			if (throwingWeaponPtr == throwingWeapon)
			{
				delete throwingWeaponPtr;
				throwingWeaponPtr = nullptr;
			}
		}
	}
}
void ThrowingWeaponsManager::DeleteWeapons( )
{
	for (ThrowingWeapon*& enemyPtr : m_ThrowingWeaponPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			delete enemyPtr;
			enemyPtr = nullptr;
		}
	}
}
