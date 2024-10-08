#include "AudioComponent.h"
#include "../ComponentManager/EngineComponentManager.h"
#include <iostream>

AudioComponent::AudioComponent(GameObject* owner) : EngineComponent(owner), mGroup(), mAudio()
{
	this->ID = "Audio";
	mGroup = AEAudioCreateGroup();
}

AudioComponent::~AudioComponent()
{
	//EngineComponentManager::getPtr()->DeleteEngine(this);

	//if(!audioName.empty())
	//	ResourceManager::GetPtr()->Unload(audioName);

	AEAudioUnloadAudioGroup(mGroup);
}

void AudioComponent::Update()
{
}

void AudioComponent::PlayAudio()
{
	s32 loops = 0;
	if (loop)
		loops = -1;

	if (!playing)
	{
		playing = true;
		AEAudioPlay(mAudio, mGroup, volume, pitch, loops);
	}
	else
		AEAudioStopGroup(mGroup);
}

void AudioComponent::SetAudio(std::string s)
{
	audioName = s;
	mAudio = *(ResourceManager::GetPtr()->Get<AudioResource>(s)->GetData());
}

void AudioComponent::LoadFromJson(const json& data)
{
	auto componentData = data.find("componentData");
	if (componentData != data.end())
	{
		//auto it = componentData->find("AudioName");
		//AudioName = it.value();
		audioName = data.at("audioName").get<std::string>();
		SetAudio(audioName);

		volume = data.at("volume").get<float>();
		pitch = data.at("pitch").get<float>();
		loop = data.at("loop").get<bool>();
		playing = data.at("playing").get<bool>();
	}
}

json AudioComponent::SaveToJson()
{
	json data, componentData;
	data["type"] = "Audio";

	componentData["audioName"] = audioName;
	componentData["volume"] = volume;
	componentData["pitch"] = pitch;
	componentData["loop"] = loop;
	componentData["playing"] = playing;

	data["componentData"] = componentData;

	return data;
}

ComponentSerializer* AudioComponent::CreateComponent(GameObject* owner)
{
	return owner->FindComponent("Audio");
}
