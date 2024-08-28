#pragma once
#include <string>
#include <queue>
#include <list>
#include <map>
#include <memory>
#include "../Resource/Resource.h"

class ResourceManager
{
	enum Extension
	{
		PNG,
		MP3,
		TTF
	};
	std::map<std::string, Extension> stringToExtention =
	{
		{"png", PNG},
		{"mp3", MP3},
		{"ttf", TTF}
	};
	//map to hold names / resource*
	std::map<Extension, std::map<std::string, std::unique_ptr<Resource>>> res;

	ResourceManager(const ResourceManager& other) = delete;
	const ResourceManager& operator= (const ResourceManager& other) = delete;

	static ResourceManager* res_ptr;

	Extension StringToExtension(const std::string&);

protected:
	ResourceManager() = default;
	~ResourceManager() = default;

public:
	static ResourceManager* GetPtr();
	static void DeletePtr();

	template <typename T>
	T* Get(const std::string&);
	void Unload(const std::string&);

	void UnloadAll(bool);

	//void printResource();
};

#include "ResourceManager.inl"