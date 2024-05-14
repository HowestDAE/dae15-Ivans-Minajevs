#pragma once
#include "Texture.h"
#include "TextureType.h"
#include <vector>

class TexturesManager
{
public:
	TexturesManager();
	static TexturesManager* GetInstance();
	void AddTexture(TextureType textureType, const std::string& fileName);
	void AddText(TextureType textureType, const std::string& text, const std::string& font, int size, Color4f color);
	Texture* GetTexture( TextureType textureType ) const;
	void DeleteTextures();
private:
	static TexturesManager* m_Instance;
	std::vector<Texture*> m_TexturePtrArr;
};
