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

void TriggersManager::DeleteTriggers()
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
void TriggersManager::UpdateTrigger( Rectf sourceRect ) const
{
	for (Trigger* triggerPtr : m_TriggersPtrArr)
	{
		if (triggerPtr != nullptr)
		{
			if (utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left, sourceRect.bottom, 10.f, sourceRect.height ) )
				|| utils::IsPointInRect(triggerPtr->GetPosition(), Rectf(sourceRect.left + sourceRect.width - 10.f, sourceRect.bottom, 10.f, sourceRect.height ))
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
	}
}
