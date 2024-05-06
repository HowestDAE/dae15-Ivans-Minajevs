#pragma once
#include <vector>

#include "Trigger.h"

class TriggersManager
{
public:
	void AddTrigger(Trigger* triggerPtr);
	void DeleteTriggers();
	void UpdateTrigger(Rectf sourceRect) const;
	std::vector<Trigger*>& GetTriggersArray();

private:
	std::vector<Trigger*> m_TriggersPtrArr;
};
