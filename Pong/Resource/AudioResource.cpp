#include "AudioResource.h"

void AudioResource::Load(const std::string& s)
{
	AEAudio audioData = AEAudioLoadMusic(s.c_str());
	data = static_cast<void*>(&audioData);
}

void AudioResource::Unload()
{
	AEAudioUnloadAudio(*(static_cast<AEAudio*>(data)));
}

AEAudio* AudioResource::GetData() const
{
	return static_cast<AEAudio*>(data);
}
