#pragma once

class SoundEffect
{
public:
	explicit SoundEffect(std::string path);
	~SoundEffect();
	SoundEffect(const SoundEffect& other) = default;
	SoundEffect& operator=(const SoundEffect& rhs) = default;

	bool IsLoaded() const;
	bool Play(int loops);
	void SetVolume(int value) const;
	int GetVolume() const;
	static void StopAll();
	static void PauseAll();
	static void ResumeAll();
	void Stop() const;


	bool IsPlaying(int channel) const;

private:
	std::shared_ptr<Mix_Chunk> m_pMixChunk;
	int m_Channel;
};
