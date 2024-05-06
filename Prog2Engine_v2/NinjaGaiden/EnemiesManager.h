#pragma once
#include <vector>
#include "ParticlesManager.h"

class Enemy;
class EnemiesManager
{
public:
	void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec,
				ParticlesManager* particlesManagerPtr, const TexturesManager* texturesManagerPtr, Rectf sourceRect);
	void Draw() const;

	void Add(Enemy* enemyPtr);

	void DeleteEnemy( const Enemy* enemy);

	void DeleteEnemies();

	std::vector<Enemy*>& GetEnemiesArray();
	
	//const std::string m_FILE_PATH { "enemies_spritesheet.png" };
private:
	std::vector<Enemy*> m_EnemiesPtrArr;
};
