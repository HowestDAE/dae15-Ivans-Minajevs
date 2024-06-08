#pragma once
#include "Biker.h"

class Boxer final : public Biker 
{
public:
	Boxer(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);

	virtual void UpdateSourceRect() override;

	virtual int GetScoreIfKilled() override;


};
