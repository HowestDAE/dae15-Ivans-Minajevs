#pragma once
#include <vector>
class Enemy;
class EnemiesManager
{
public:
	void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec);
	void Draw() const;

	void Add(Enemy* enemyPtr);

	std::vector<Enemy*>& GetEnemiesArray();
	
	//const std::string m_FILE_PATH { "enemies_spritesheet.png" };
private:
	std::vector<Enemy*> m_EnemiesPtrArr;
};
