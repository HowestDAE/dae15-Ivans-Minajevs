#pragma once
#include <vector>


#include "CollectibleTrigger.h"
#include "EnemyTrigger.h"
#include "LanternsManager.h"
#include "Trigger.h"
#include "TriggerType.h"

class TriggersManager final
{
public:
	void AddTrigger(Trigger* triggerPtr);

	
	void DeleteTriggers( );
	void DeleteTrigger(const Trigger* triggerPtr);
	
	void UpdateTrigger(Rectf sourceRect, MovementDirection ryuDirection) const;

	std::vector<Trigger*>& GetTriggersArray(  );


private:
	std::vector<Trigger*> m_TriggersPtrArr;
};
