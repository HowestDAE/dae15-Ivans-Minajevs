#include "pch.h"
#include "LanternsManager.h"

#include "utils.h"
void LanternsManager::Update( float elapsedSec, const TexturesManager* texturesManagerPtr, Rectf sourceRect )
{
	for (Lantern*& lanternPtr : m_LanternsPtrArr)
	{
		if (lanternPtr != nullptr)
		{
			lanternPtr->Update(elapsedSec);
			
			//if (!utils::IsOverlapping(lanternPtr->GetSourceRect(), sourceRect))
			//{
			//	DeleteLantern(lanternPtr);
			//}
			//
			//else if (!lanternPtr->GetIsExisting())
			//{
			//	DeleteLantern(lanternPtr);
			//}
		}
	}
}
void LanternsManager::Draw( ) const
{
	for (Lantern* lanternPtr : m_LanternsPtrArr)
	{
		if (lanternPtr != nullptr)
		{
			lanternPtr->Draw();
		}
	}
}
void LanternsManager::Add( Lantern* lanternPtr )
{
	m_LanternsPtrArr.push_back(lanternPtr);
}

void LanternsManager::DeleteLantern( const Lantern* lantern )
{
	for (Lantern*& lanternPtr : m_LanternsPtrArr)
	{
		if (lanternPtr != nullptr && lantern != nullptr)
		{
			if (lanternPtr == lantern)
			{
				delete lanternPtr;
				lanternPtr = nullptr;
			}
		}
	}
}

void LanternsManager::DeleteLanterns( )
{
	for (Lantern*& lanternPtr : m_LanternsPtrArr)
	{
		if (lanternPtr != nullptr)
		{
			delete lanternPtr;
			lanternPtr = nullptr;
		}
	}
}
std::vector<Lantern*>& LanternsManager::GetLanternsArray( )
{
	return m_LanternsPtrArr;
}


