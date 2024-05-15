#pragma once
#include "Biker.h"

class Boxer : public Biker
{
public:
	Boxer(const Ryu* ryuPtr, const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	
	void UpdateSourceRect() override;

	int GetScoreIfKilled() override;


};
