#pragma once
#include <vector>
#include "ParticleType.h"

class Particle;
class ParticlesManager
{
public:
	void Update(float elapsedSec);
	void Draw() const;

	void Add(ParticleType type, Point2f pos, float timeAlive);

private:
	std::vector<Particle*> m_ParticlesArr;
};
