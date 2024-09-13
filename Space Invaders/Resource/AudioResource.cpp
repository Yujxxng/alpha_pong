#include "AudioResource.h"
#include <iostream>
void AudioResource::Load(const std::string& s)
{
	audioData = AEAudioLoadMusic(s.c_str());
	data = static_cast<void*>(&audioData);
}

AudioResource::AudioResource()
{
}

AudioResource::~AudioResource()
{
	Unload();
}

void AudioResource::Unload()
{
	AEAudioUnloadAudio(*(static_cast<AEAudio*>(data)));
}

AEAudio* AudioResource::GetData() const
{
	return static_cast<AEAudio*>(data);
}
