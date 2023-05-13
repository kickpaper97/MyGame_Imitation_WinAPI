#include "GameEnginePath.h"
#include<GameEngineBase/GameEngineDebug.h>


GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::string& _path)
	:Path(_path)
{
}

GameEnginePath::~GameEnginePath()
{
}

void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}

void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
		
	std::filesystem::path CheckPath = Path;
	
	while (true)
	{
		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert("루트 경로까지" + _ChildPath + "파일 을 하위로 가지고있는 경로를 찾지 못했습니다.");
		}
	}
}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로에 이동하려 시도했습니다." + CheckPath.string());
	}

	Path = CheckPath;
}
