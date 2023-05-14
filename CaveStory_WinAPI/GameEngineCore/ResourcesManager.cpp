#include "ResourcesManager.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

ResourcesManager ResourcesManager::Inst;

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
	for (const std::pair<std::string,GameEngineWindowTexture*>& pair:AllTexture)
	{
		GameEngineWindowTexture* Texture = pair.second;

		if (nullptr != Texture)
		{
			delete Texture;
			Texture = nullptr;
		}
	}
}

GameEngineWindowTexture* ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineWindowTexture* LoadTexture = new GameEngineWindowTexture();

	LoadTexture->ResLoad(_Path);

	AllTexture.insert(std::make_pair(UpperName, LoadTexture));

	return LoadTexture;
}

GameEngineWindowTexture* ResourcesManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineWindowTexture*>::iterator Finder = AllTexture.find(UpperName);
	if (Finder == AllTexture.end())
	{
		return nullptr;
	}
	return Finder->second;
}

bool ResourcesManager::IsLoadTexture(const std::string& _Image)
{
	return FindTexture(_Image) != nullptr;
}
