#pragma once

#include "Texture.h"
#include "ThrowingWeaponType.h"
#include "Vector2f.h"

class ThrowingWeapon final
{
public:
	ThrowingWeapon( ThrowingWeaponType type, const Point2f& position, const Vector2f& velocity, bool isFriend);

	void Update(float elapsedSec);
	void UpdateSourceRect();
	void ChangeFrames(float elapsedSec);
	
	Rectf GetCollisionRect() const;
	bool GetIsFriendly() const ;
	Vector2f GetThrowingWeaponVelocity() const;
	
	void Draw() const;

	static const int m_CELL_COUNT;

	static const float m_SCALE;

	static const float m_FRAME_TIME;
private:
	ThrowingWeaponType m_Type;
	Texture* m_TexturePtr;
	Point2f m_Position;
	Vector2f m_Velocity;
	Rectf m_SourceRect;
	Rectf m_CollisionRect;
	float m_TextureCellWidth;

	float m_AccuSec{ 0.f };
	bool m_IsFriend;
	int m_InitFrameNr;
	int m_FrameNr;
	int m_FramesCount;
};
