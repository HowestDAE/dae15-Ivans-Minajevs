#pragma once
#include <vector>


#include "CollectibleTrigger.h"
#include "EnemyTrigger.h"
#include "Trigger.h"
#include "TriggerType.h"

class TriggersManager
{
public:
	void AddTrigger(Trigger* triggerPtr);

	
	void DeleteTriggers( );
	
	void UpdateTrigger(Rectf sourceRect, MovementDirection) const;

	std::vector<Trigger*>& GetTriggersArray(  );


private:
	std::vector<Trigger*> m_TriggersPtrArr;
};
