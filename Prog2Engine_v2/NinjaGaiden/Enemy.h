#pragma once
#include <vector>

#include "EnemyAreaBorders.h"
#include "MovementDirection.h"
#include "Ryu.h"
#include "Texture.h"
#include "TextureManager.h"
class Enemy
{
public:
    enum class EnemyType
    {
        biker, boxer, dog, knifeMan
    };
    
    Enemy(float startPosX, float endPosX, const Ryu* ryuPtr, const TexturesManager* texturesManagerPtr, Point2f position, Point2f velocity);
    //virtual ~Enemy() = default;
    
    virtual void Draw() const;
    virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) = 0;
    
    void HandleVerticalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices);
    virtual void HandleHorizontalCollision(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices);
    void HandleBorders();
    void ChangeDirection();
    
    virtual void UpdateSourceRect() = 0;
    virtual void ChangeFrames(float elapsedSec) = 0;
    
    void ChangePosition(float elapsedSec);
    void UpdateJump(float elapsedSec);

    Point2f GetPosition() const;
    Rectf GetSourceRect() const;
    bool GetIsAlive() const;
    void SetIsAlive(bool isAlive);
    
    const float m_SCALE { 3.f };
    const int m_COLS{ 6 };
    const int m_ROWS { 4 };

protected:
    Point2f m_Velocity;
    Rectf m_SourceRect;
    MovementDirection m_MovementDirection;
    Texture* m_EnemiesTexturePtr;

    float m_AccuSec { 0 };
    
private:
    Point2f m_Position;
    bool m_IsAlive;
    const Ryu* m_RyuPtr;
    EnemyAreaBorders m_AreaBorders;
};

