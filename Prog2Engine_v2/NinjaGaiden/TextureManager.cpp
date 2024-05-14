#include "pch.h"
#include "TextureManager.h"
#include "Game.h"
#include "Texture.h"

TexturesManager* TexturesManager::m_Instance{ nullptr };

TexturesManager* TexturesManager::GetInstance()
{
	return m_Instance;
}

TexturesManager::TexturesManager( )
{
	if (m_Instance == nullptr)
	{
		m_Instance = this;
	}
	m_TexturePtrArr.resize(static_cast<int>(TextureType::count));
}


void TexturesManager::AddTexture( TextureType textureType, const std::string& fileName )
{
	if (m_TexturePtrArr[static_cast<int>(textureType)] == nullptr)
	{
		m_TexturePtrArr[static_cast<int>(textureType)] = new Texture(fileName);
	}
}
void TexturesManager::AddText( TextureType textureType, const std::string& text, const std::string& font, int size, Color4f color )
{
	if (m_TexturePtrArr[static_cast<int>(textureType)] == nullptr)
	{
		m_TexturePtrArr[static_cast<int>(textureType)] = new Texture(text, font, size, color);
	}
}
Texture* TexturesManager::GetTexture( TextureType textureType ) const
{
	return m_TexturePtrArr[static_cast<int>(textureType)];
}

void TexturesManager::DeleteTextures( )
{
	for (Texture*& texture : m_TexturePtrArr)
	{
		if (texture != nullptr)
		{
			delete texture;
			texture = nullptr;
		}
	}
}

