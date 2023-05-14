
#pragma once
#include <string>
#include<map>
#include <GameEngineBase/GameEnginePath.h>


class GameEngineWindowTexture;
class ResourcesManager
{
public:

	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(const ResourcesManager&& _Other) noexcept = delete;

	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);
	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	bool IsLoadTexture(const std::string& _Image);

protected:

private:
	ResourcesManager();
	~ResourcesManager();

	static ResourcesManager Inst;

	std::map<std::string, GameEngineWindowTexture*> AllTexture;

};

