#pragma once
#include "SoundEffect.h"
#include "SoundStream.h"
#include "Singleton.h"

namespace cem
{

	class SoundManager : public cem::Singleton<SoundManager>
	{
	public:
		SoundManager();

		void InitSoundStreams();
		void InitSoundEffects();

		// SOUND STREAM
		void PlaySoundStream(const std::string& name, bool repeat);
		void VolumeUpSoundStream();
		void VolumeDownSoundStream();
		int GetVolumeSoundStream();

		// SOUND-EFFECTS
		void PlaySoundEffect(const std::string& name, bool repeat, bool isPlaying);
		void VolumeUpSoundEffect();
		void VolumeDownSoundEffect();
		int GetVolumeSoundEffect();
		void StopSoundEffect(const std::string& name);
		void StopMusic(const std::string& name);

		// EXTRA
		bool IsPlaying(std::string name);
		void StopAll();

	private:
		std::map<std::string, SoundStream> m_SoundStreamMap;
		std::map<std::string, SoundEffect> m_SoundEffectMap;
	};
}