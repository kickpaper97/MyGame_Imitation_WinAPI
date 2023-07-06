#include "Arthur_sHouse.h"
#include "ContentsEnum.h"
#include"CureMachine.h"
#include"TelePorter.h"
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
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MimigaVillage-Arthur'sHouse-Col.Bmp"));

	}

	if (nullptr == GameEngineSound::FindSound("Safety.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Safety.mp3"));


	}



	BackGround* FrontPtr = CreateActor<BackGround>(RenderOrder::FrontGround);
	FrontPtr->Init("MimigaVillage-Arthur'sHouse-Front.Bmp");




	Ptr = CreateActor<BackGround>(RenderOrder::BackGround);
	Ptr->Init("MimigaVillage-Arthur'sHouse.Bmp", "MimigaVillage-Arthur'sHouse-Col.Bmp");

	LevelPlayer = CreateActor<Player>(RenderOrder::MiddlePlay);

	LevelPlayer->SetGroundTexture("MimigaVillage-Arthur'sHouse.Bmp");
	LevelPlayer->SetActorBoundery("MimigaVillage-Arthur'sHouse-Col.Bmp");
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


	LevelPlayer->SetGroundTexture("MimigaVillage-Arthur'sHouse-Col.Bmp");
	LevelPlayer->SetActorBoundery("MimigaVillage-Arthur'sHouse.Bmp");

	BGMPlayer = GameEngineSound::SoundPlay("Safety.mp3");
	BGMPlayer.SetLoop(10000);


	{
		TelePorter* NewTeleporter = CreateActor<TelePorter>();
		NewTeleporter->SetPos({ 480 ,505 });
		NewTeleporter->SetDestination("EggCorridor");
		
		
	}
	
}

void Arthur_sHouse::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}