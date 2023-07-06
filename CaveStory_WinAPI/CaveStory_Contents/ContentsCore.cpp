#include "ContentsCore.h"
#include"TitleLevel.h"
#include"FirstCave_StartPointLevel.h"
#include "EndingLevel.h"
#include"EggCorridor.h"
#include"Arthur_sHouse.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 200,30 }, { 1280, 960 });
	
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	//GameEngineCore::CreateLevel<FirstCave_StartPointLevel>("FirstCave_startPointLevel");

	GameEngineCore::CreateLevel<EggCorridor>("EggCorridor");
	//GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	GameEngineCore::CreateLevel<Arthur_sHouse>("Arthur_sHouse");
	GameEngineCore::CreateLevel<EndingLevel>("Ending");


	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{
}


void ContentsCore::Release()
{
}
