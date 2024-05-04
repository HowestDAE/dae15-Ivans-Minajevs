#pragma once
#include "Biker.h"

class Boxer : public Biker
{
public:
	Boxer(float startPosX, float endPosX,const Ryu* ryuPtr, TexturesManager* texturesManager, Point2f position, Point2f velocity);
	void UpdateSourceRect() override;
};
