#pragma once
#include <vector>

#include "EnemyAreaBorders.h"
#include "MovementDirection.h"
#include "Ryu.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Trigger.h"
class Enemy
{
public:
    virtual ~Enemy() = default;
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;
    Enemy(Enemy&&) = delete;
    Enemy& operator=(Enemy&&) = delete;

    Enemy(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
    
    virtual void Draw() const;
    virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec);
    
    void HandleVerticalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices);
    void HandleHorizontalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices);
    void ChangeDirection();
    
    virtual void UpdateSourceRect() = 0;
    virtual void ChangeFrames(float elapsedSec) = 0;

    virtual int GetScoreIfKilled() = 0 ;
    
    void ChangePosition(float elapsedSec);
    void UpdateJump(float elapsedSec);

    const Trigger * GetTriggerPointer( ) const;
    Point2f GetPosition() const;
    Rectf GetCollisionRect() const;
    bool GetIsAlive() const;
    void SetIsAlive(bool isAlive);
    MovementDirection GetDirection() const;

    EnemyType GetEnemyType() const;

   static const float m_SCALE;
   static const float m_VERTICAL_VELOCITY;
   static const int m_COLS;
   static const int m_ROWS;

protected:
    EnemyType m_EnemyType;
    Point2f m_Position;
    Point2f m_Velocity;
    
    Rectf m_SourceRect;
    MovementDirection m_MovementDirection;
    Texture* m_EnemiesTexturePtr;

    float m_HorizontalVelocity;

    float m_TextureCellWidth;
    float m_AccuSec { 0.f };
    Rectf m_CollisionRect;
    
private:
    const Trigger* m_TriggerPtr;
    bool m_IsAlive;
};

