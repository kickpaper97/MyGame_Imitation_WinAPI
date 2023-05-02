#include "ContentsCore.h"
#include"TitleLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update()
{
}

void ContentsCore::Render()
{
}

void ContentsCore::Release()
{
}
