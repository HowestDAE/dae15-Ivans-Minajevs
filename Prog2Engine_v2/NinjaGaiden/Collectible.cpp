#include "pch.h"
#include "Collectible.h"
Collectible::Collectible( Point2f position, CollectibleType type, const TexturesManager* texturesManagerPtr )
	: m_Position(position), m_Type(type), m_TexturesManagerPtr(texturesManagerPtr)
{
	
}
void Collectible::Draw( ) const
{
}
void Collectible::Update( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec )
{
}
void Collectible::HandleVerticalCollision( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices )
{
}
void Collectible::UpdateJump( )
{
}
