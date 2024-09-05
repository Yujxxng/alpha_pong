#pragma once

#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/EngineComponentManager.h"
#include "../ComponentManager/ResourceManager.h"
#include "../Resource/AudioResource.h"

#include "AEAudio.h"

#include <string>

class AudioComponent : public EngineComponent
{
	AEAudioGroup mGroup;
	AEAudio mAudio;
	std::string audioName;

	float volume = 0.25f;
	float pitch = 1;

	bool loop = true;
	bool playing = false;
public:
	AudioComponent() = delete;
	AudioComponent(GameObject* owner);
	~AudioComponent();

	void Update() override;

	void SetAudio(std::string s);
	void SetPlay(bool p) { playing = p; }
	void SetPause();
	void Setloop(bool p) { loop = p; }

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);
};