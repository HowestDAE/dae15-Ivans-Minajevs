#pragma once
#include "CollectibleType.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Trigger.h"

class Lantern final
{
public:

	Lantern(Point2f position, CollectibleType collectibleType, Trigger* triggerPtr, const TexturesManager* texturesManagerPtr);

	void Update(float elapsedSec);
	void Draw() const;

	void UpdateSourceRect();
	void ChangeFrames(float elapsedSec);

	void SetIsExisting(bool isExisting);

	Point2f GetPosition() const;
	CollectibleType GetCollectibleType() const;
	bool GetIsExisting() const;
	Rectf GetSourceRect() const;


	
	Trigger* GetTriggerPointer( ) const;

	static const float m_SCALE;
	static const int m_FRAMES_PER_SEC;
	static const float m_FRAME_TIME ;
	static const int m_COLS ;
	static const int m_ROWS;
	static const int m_FRAMES_COUNT;
private:
	Trigger* m_TriggerPtr;
	Point2f m_Position;
	CollectibleType m_CollectibleType;
	bool m_IsExisting { true };

	Rectf m_SourceRect;
	Texture* m_LanternTexturePtr;
	float m_AccuSec { 0 };

	int m_FrameNr { 0 };
};
