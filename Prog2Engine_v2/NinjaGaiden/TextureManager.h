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
	Texture* GetTexture( TextureType textureType ) const;
	void DeleteTextures();
private:
	static TexturesManager* m_Instance;
	std::vector<Texture*> m_TexturePtrArr;
};
