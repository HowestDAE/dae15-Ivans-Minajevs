#pragma once
#include <vector>
class Enemy
{
public:
    enum class EnemyDirection { left, right };
    //enum class EnemyState{ }; 
    
    Enemy(Point2f position, Point2f velocity, Rectf sourceRect);
    
    virtual void Draw() const = 0;
    virtual void Update() = 0;

    void HandleFloorCollision(const std::vector<std::vector<Point2f>>& vertices);
    void HandleSignsCollision(const std::vector<std::vector<Point2f>>& vertices);
    void HandlePlatformsCollision(const std::vector<std::vector<Point2f>>& vertices);
    void HandleWallsCollision(const std::vector<std::vector<Point2f>>& vertices);

    //void DrawDeathParticle() const;
    void UpdateSourceRect(Rectf newRect);
private:
    Point2f m_Position;
    Point2f m_Velocity;
    Rectf m_SourceRect;

    //void UpdateSourceRect();
    
};

