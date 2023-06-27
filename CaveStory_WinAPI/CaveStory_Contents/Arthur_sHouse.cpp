#include "Arthur_sHouse.h"
#include "ContentsEnum.h"
#include"CureMachine.h"
#include"PlayUIManager.h"
#include"Player.h"
#include "BackGround.h"

#include<GameEngineBase/GameEngineDebug.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>

Arthur_sHouse::Arthur_sHouse()
{
}

Arthur_sHouse::~Arthur_sHouse()
{
}


void Arthur_sHouse::Start()
{


	if (false == ResourcesManager::GetInst().IsLoadTexture("MimigaVillage-Arthur'sHouse.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Map");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MimigaVillage-Arthur'sHouse.Bmp"));
	}



	BackGround* FrontPtr = CreateActor<BackGround>(RenderOrder::FrontGround);
	FrontPtr->Init("MimigaVillage-Arthur'sHouse-Front.Bmp");




	Ptr = CreateActor<BackGround>(RenderOrder::BackGround);
	Ptr->Init("MimigaVillage-Arthur'sHouse.Bmp", "MimigaVillage-Arthur'sHouse_Col.Bmp");

	LevelPlayer = CreateActor<Player>(RenderOrder::MiddlePlay);

	LevelPlayer->SetGroundTexture("MimigaVillage-Arthur'sHouse.Bmp");
	LevelPlayer->SetActorBoundery("MimigaVillage-Arthur'sHouse_Col.Bmp");
	LevelPlayer->SetPos(float4{ 925 ,500 });


	 CreateActor<PlayUIManager>();
}

void Arthur_sHouse::Update(float _Delta)
{
}

void Arthur_sHouse::LevelStart(GameEngineLevel* _PrevLevel)
{


	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}


	LevelPlayer->SetGroundTexture("EggCorridor_Ground.Bmp");
	LevelPlayer->SetActorBoundery("EggCorridor_Middle.Bmp");
}

void Arthur_sHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
}