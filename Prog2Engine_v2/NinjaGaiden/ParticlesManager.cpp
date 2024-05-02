#include "pch.h"
#include "ParticlesManager.h"
#include "Particle.h"

void ParticlesManager::Update(float elapsedSec)
{
	for (Particle*& particle : m_ParticlesArr)
	{
		if (particle != nullptr)
		{
			particle->ChangeTimeAlive(particle->GetTimeAlive() - elapsedSec);
			particle->Update(elapsedSec);
			if (particle->GetTimeAlive() < 0.f)
			{
				delete particle;
				particle = nullptr;
			}
		}
	}
}

void ParticlesManager::Draw( ) const
{
	for (Particle* particle : m_ParticlesArr)
	{
		if (particle != nullptr)
		{
			particle->Draw();
		}
	}
}

void ParticlesManager::Add(ParticleType type, Point2f pos, float timeAlive) 
{
	m_ParticlesArr.push_back(new Particle(type, pos, timeAlive));
}
