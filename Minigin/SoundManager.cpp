#include "MiniginPCH.h"
#include "SoundManager.h"

namespace cem
{

	SoundManager::SoundManager()
	{
		InitSoundEffects();
		InitSoundStreams();
	}

	void SoundManager::InitSoundStreams()
	{
		m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("Menu", SoundStream{ "../Resources/Sound/Music/Menu.mp3" }));
		m_SoundStreamMap.begin()->second.SetVolume(35);
	}

	void SoundManager::InitSoundEffects()
	{
		m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Confirm", SoundEffect{ "../Resources/Sound/Sound_Effects/MenuConfirm.mp3" }));
		m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Move", SoundEffect{ "../Resources/Sound/Sound_Effects/MenuMove.mp3" }));
		m_SoundEffectMap.begin()->second.SetVolume(30);
	}

	void SoundManager::PlaySoundStream(const std::string& name, bool repeat)
	{
		auto it = m_SoundStreamMap.find(name);

		if (it != m_SoundStreamMap.end())
		{
			it->second.Play(repeat);
		}
	}

	void SoundManager::PlaySoundEffect(const std::string& name, bool repeat, bool isPlaying)
	{

		auto it = m_SoundEffectMap.find(name);

		if (it != m_SoundEffectMap.end())
		{
			it->second.Play(repeat);

			if (isPlaying)
			{
				if (!IsPlaying(name))
				{
					it->second.Play(repeat);
				}
			}
			else
			{
				it->second.Play(repeat);
			}
		}
	}


	void SoundManager::VolumeUpSoundEffect()
	{
		m_SoundEffectMap.begin()->second.SetVolume(m_SoundEffectMap.begin()->second.GetVolume() + 10);

		if (m_SoundEffectMap.begin()->second.GetVolume() >= 100)
		{
			m_SoundEffectMap.begin()->second.SetVolume(100);
		}
	}

	void SoundManager::VolumeDownSoundEffect()
	{
		if (m_SoundEffectMap.begin()->second.GetVolume() <= 10)
		{
			m_SoundEffectMap.begin()->second.SetVolume(0);
		}
		else
		{
			m_SoundEffectMap.begin()->second.SetVolume(m_SoundEffectMap.begin()->second.GetVolume() - 10);
		}
		std::cout << m_SoundEffectMap.begin()->second.GetVolume() << std::endl;
	}

	int SoundManager::GetVolumeSoundEffect()
	{
		return m_SoundEffectMap.begin()->second.GetVolume();
	}

	void SoundManager::StopSoundEffect(const std::string& name)
	{
		m_SoundEffectMap.find(name)->second.Stop();
	}

	void SoundManager::StopMusic(const std::string& name)
	{
		m_SoundStreamMap.find(name)->second.Stop();
	}


	void SoundManager::VolumeUpSoundStream()
	{
		m_SoundStreamMap.begin()->second.SetVolume(m_SoundStreamMap.begin()->second.GetVolume() + 10);

		if (m_SoundStreamMap.begin()->second.GetVolume() >= 100)
		{
			m_SoundStreamMap.begin()->second.SetVolume(100);
		}
	}

	void SoundManager::VolumeDownSoundStream()
	{
		if (m_SoundStreamMap.begin()->second.GetVolume() <= 10)
		{
			m_SoundStreamMap.begin()->second.SetVolume(0);
		}
		else
		{
			m_SoundStreamMap.begin()->second.SetVolume(m_SoundStreamMap.begin()->second.GetVolume() - 10);
		}
		std::cout << m_SoundStreamMap.begin()->second.GetVolume() << std::endl;
	}

	int SoundManager::GetVolumeSoundStream()
	{
		return m_SoundStreamMap.begin()->second.GetVolume();
	}

	bool SoundManager::IsPlaying(std::string name)
	{
		for (int i = 0; i < Mix_AllocateChannels(-1); i++)
		{
			if (m_SoundEffectMap.find(name)->second.IsPlaying(i))
			{
				return true;
			}
		}
		return false;
	}

	void SoundManager::StopAll()
	{
		StopSoundEffect("Confirm");
		StopSoundEffect("Move");
		StopMusic("Menu");
	}
}
