#include "pch.h"
#include "SoundEffectsManager.h"

#include "SoundEffect.h"

SoundEffectsManager* SoundEffectsManager::m_Instance{ nullptr };

SoundEffectsManager* SoundEffectsManager::GetInstance()
{
	return m_Instance;
}

SoundEffectsManager::SoundEffectsManager( )
{
	if (m_Instance == nullptr)
	{
		m_Instance = this;
	}
	 m_SoundEffectsPtrArr.resize(static_cast<int>(SoundEffectType::count));
}


void SoundEffectsManager::AddSoundEffect( SoundEffectType soundEffectType, const std::string& fileName )
{
	if ( m_SoundEffectsPtrArr[static_cast<int>(soundEffectType)] == nullptr)
	{
		 m_SoundEffectsPtrArr[static_cast<int>(soundEffectType)] = new SoundEffect(fileName);
	}
}

SoundEffect* SoundEffectsManager::GetSoundEffect( SoundEffectType soundEffectType) const
{
	return  m_SoundEffectsPtrArr[static_cast<int>(soundEffectType)];
}

void SoundEffectsManager::DeleteSoundEffects( )
{
	for (SoundEffect*& soundEffectPtr : m_SoundEffectsPtrArr)
	{
		if (soundEffectPtr != nullptr)
		{
			delete soundEffectPtr;
			soundEffectPtr = nullptr;
		}
	}
}