#pragma once
#include <vector>
#include "ParticleType.h"
#include "TextureManager.h"

class Particle;
class ParticlesManager
{
public:
	void Update(float elapsedSec);
	void Draw() const;

	void Add(const TexturesManager* texturesManager, ParticleType particleType, Point2f pos, float timeAlive);
	void DeleteParticles();

private:
	std::vector<Particle*> m_ParticlesArr;
};
