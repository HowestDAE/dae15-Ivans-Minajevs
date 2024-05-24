#include "pch.h"
#include "TriggersManager.h"

#include "utils.h"
void TriggersManager::AddTrigger( Trigger* triggerPtr )
{
	m_TriggersPtrArr.push_back(triggerPtr);
}

std::vector<Trigger*>& TriggersManager::GetTriggersArray( )
{
	return m_TriggersPtrArr;
}


void TriggersManager::DeleteTriggers(  )
{
	for (Trigger*& triggerPtr : m_TriggersPtrArr)
	{
		if (triggerPtr != nullptr)
		{
			delete triggerPtr;
			triggerPtr = nullptr;
		}
	}
	
}
void TriggersManager::DeleteTrigger(const Trigger* triggerPtr )
{
	for (Trigger*& triggerSrcPtr : m_TriggersPtrArr)
	{
		if (triggerSrcPtr != nullptr && triggerPtr != nullptr)
		{
			if (triggerSrcPtr == triggerPtr)
			{
				delete triggerSrcPtr;
				triggerSrcPtr = nullptr;
			}
		}
	}
}

void TriggersManager::UpdateTrigger( Rectf sourceRect, MovementDirection ryuDirection) const
{
	for (Trigger* triggerPtr : m_TriggersPtrArr)
	{
		if (triggerPtr != nullptr)
		{
			if (!triggerPtr->GetIsActivated())
			{
				triggerPtr->SetActivated(true);
			}
			else if (triggerPtr->GetIsActivated())
			{
				triggerPtr->SetActivated(false);
			}
			if (triggerPtr->GetTriggerType() == TriggerType::enemy)
			{
				
				if (
			
				(triggerPtr->GetEnemyType() != EnemyType::dog && triggerPtr->GetEnemyType() != EnemyType::boss &&
				(ryuDirection == MovementDirection::left && utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left, sourceRect.bottom, 10.f, sourceRect.height ) )||
				 ryuDirection == MovementDirection::right && utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left + sourceRect.width - 10.f, sourceRect.bottom, 10.f, sourceRect.height ))))
	
				|| triggerPtr->GetEnemyType() == EnemyType::dog &&
				(triggerPtr->GetInitMovementDirection() == MovementDirection::right && utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left, sourceRect.bottom, 10.f, sourceRect.height ) ))||
				(triggerPtr->GetInitMovementDirection() == MovementDirection::left && utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left + sourceRect.width - 10.f, sourceRect.bottom, 10.f, sourceRect.height )))

				|| triggerPtr->GetEnemyType() == EnemyType::boss &&
				(
					utils::IsPointInRect(triggerPtr->GetPosition(), sourceRect)	
				)
				)
				{
					if (!triggerPtr->GetIsActivated())
					{
						triggerPtr->SetActivated(true);
					}
				}
				else
				{
					if (triggerPtr->GetIsActivated())
					{
						triggerPtr->SetActivated(false);
					}
				}
			}
			else if (triggerPtr->GetTriggerType() == TriggerType::collectible)
			{
				if (ryuDirection == MovementDirection::left && utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left, sourceRect.bottom, 10.f, sourceRect.height ) )||
				   ryuDirection == MovementDirection::right && utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left + sourceRect.width - 10.f, sourceRect.bottom, 10.f, sourceRect.height )))
				{
					if (!triggerPtr->GetIsActivated())
					{
						triggerPtr->SetActivated(true);
					}
				}
				else
				{
					if (triggerPtr->GetIsActivated())
					{
						triggerPtr->SetActivated(false);
					}
				}
			}
		}
	}
}
