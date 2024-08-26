#include "AudioComponent.h"
#include "../ComponentManager/EngineComponentManager.h"

AudioComponent::AudioComponent(GameObject* owner) : EngineComponent(owner), mGroup(), mAudio()
{
	this->ID = "Audio";
	mGroup = AEAudioCreateGroup();
}

AudioComponent::~AudioComponent()
{
	EngineComponentManager::getPtr()->DeleteEngine(this);

	AEAudioUnloadAudio(mAudio);
	AEAudioUnloadAudioGroup(mGroup);

	delete this;
}

void AudioComponent::Update()
{
	int loops = 0;
	if (loop)
		loops = -1;

	if (!playing)
	{
		playing = true;
		AEAudioPlay(mAudio, mGroup, volume, pitch, loops);
	}
}

void AudioComponent::SetAudio(string s)
{

	mAudio = AEAudioLoadMusic(s.c_str());
};
