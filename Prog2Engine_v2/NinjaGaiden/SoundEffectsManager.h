#pragma once
#include <vector>
#include "SoundEffectsType.h"

class SoundEffect;
class SoundEffectsManager final
{
public:
	SoundEffectsManager();
	static SoundEffectsManager* GetInstance();
	void AddSoundEffect(SoundEffectType soundEffectType, const std::string& fileName);
	SoundEffect* GetSoundEffect( SoundEffectType soundEffectType ) const;
	void DeleteSoundEffects();
private:
	static SoundEffectsManager* m_Instance;
	std::vector<SoundEffect*> m_SoundEffectsPtrArr;
};
