#pragma once
#include "CollectibleType.h"
#include "Texture.h"
#include "TextureManager.h"

class Lantern
{
public:

	Lantern(Point2f position, CollectibleType collectibleType, const TexturesManager* texturesManagerPtr);

	void Update(float elapsedSec);
	void Draw() const;

	void UpdateSourceRect();
	void ChangeFrames(float elapsedSec);

	void SetIsExisting(bool isExisting);

	Point2f GetPosition() const;
	CollectibleType GetCollectibleType() const;
	bool GetIsExisting() const;
	Rectf GetSourceRect() const;
	

	const float m_SCALE{ 2.5f };
	const int m_FRAMES_PER_SEC { 4 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
	const int m_COLS { 10 };
	const int m_ROWS { 2 };
	const int m_FRAMES_COUNT { 2 };
private:
	Point2f m_Position;
	CollectibleType m_CollectibleType;
	bool m_IsExisting { true };

	Rectf m_SourceRect;
	Texture* m_LanternTexturePtr;
	float m_AccuSec { 0 };

	int m_FrameNr { 0 };
};
