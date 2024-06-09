#pragma once
#include "EnemiesManager.h"
#include "TextureManager.h"
#include "ThrowingWeaponType.h"
#include "Vector2f.h"

class Ryu;
class ThrowingWeapon;
class ThrowingWeaponsManager final
{
public:
	void Update(float elapsedSec, Rectf viewRect, Ryu* ryuPtr, EnemiesManager* enemiesManagerPtr);
	void Draw() const;

	void Add(ThrowingWeaponType type, Point2f initPos, Vector2f initVelocity, bool isFriend);

	std::vector<ThrowingWeapon*>& GetWeaponArray(  );
	void DeleteWeapon(const ThrowingWeapon* throwingWeapon);
	void DeleteWeapons();

private:
	std::vector<ThrowingWeapon*> m_ThrowingWeaponPtrArr;
};
