#include "ResourceManager.h"
#include <stdexcept>
#include <iostream>

ResourceManager* ResourceManager::res_ptr = nullptr;


ResourceManager* ResourceManager::GetPtr()
{
	if (res_ptr == nullptr)
	{
		res_ptr = new ResourceManager;
		return res_ptr;
	}
	else
		return res_ptr;
}

void ResourceManager::DeletePtr()
{
	if (res_ptr != nullptr)
	{
		delete res_ptr;
		res_ptr = nullptr;
	}
}

ResourceManager::Extension ResourceManager::StringToExtension(const std::string& filename)
{
	std::string ext = filename.substr(filename.find_last_of('.') + 1);

	if (stringToExtention.find(ext) == stringToExtention.end())
		throw std::invalid_argument("[ERROR] ResourceManager StringToExtension | Invalid file name " + filename);
	return stringToExtention[ext];
}

void ResourceManager::Unload(const std::string& filename)
{
	Extension ext = StringToExtension(filename);

	if (res[ext].find(filename) == res[ext].end())
	{
		std::cerr << "[ERROR] ResourceManager Unload | Invalid resource " + filename << std::endl;
		return;
	}

	res[ext][filename]->counter--;

	if (res[ext][filename]->counter == 0 && !res[ext][filename]->persistent)
		this->res[ext].erase(filename);
}

void ResourceManager::UnloadAll(bool persistent)
{
	for (auto it = res.begin(); it != res.end(); )
	{
		for (auto i = it->second.begin(); i != it->second.end(); )
		{
			if (persistent || !i->second->persistent)
				it->second.erase(i++);
			else
				i++;
		}
		res.erase(it++);
	}
}
