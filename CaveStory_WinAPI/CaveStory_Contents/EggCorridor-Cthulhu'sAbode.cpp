
#include "EggCorridor-Cthulhu'sAbode.h"


#include "ContentsEnum.h"
#include"Monster.h"
#include"MonsterCutter.h"

#include<GameEngineBase/GameEngineDebug.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>



#include"Player.h"
#include "BackGround.h"
EggCorridor_Cthulhu_sAbode::EggCorridor_Cthulhu_sAbode()
{
}

EggCorridor_Cthulhu_sAbode::~EggCorridor_Cthulhu_sAbode()
{
}

void EggCorridor_Cthulhu_sAbode::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("EggCorridor-Cthulhu'sAbode _col.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Map");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EggCorridor-Cthulhu'sAbode _col.Bmp"));
	}



	BackGround* BGPtr = CreateActor<BackGround>(RenderOrder::FrontGround);
	BGPtr->Init("EggCorridor-Cthulhu'sAbode_.Bmp");




	MiddlePtr = CreateActor<BackGround>(RenderOrder::BackGround);
	MiddlePtr->Init("EggCorridor-Cthulhu'sAbode_.Bmp", "EggCorridor-Cthulhu'sAbode_Col.Bmp");

	LevelPlayer = CreateActor<Player>(RenderOrder::MiddlePlay);

	LevelPlayer->SetGroundTexture("EggCorridor-Cthulhu'sAbode_Col.Bmp");
	LevelPlayer->SetActorBoundery("EggCorridor-Cthulhu'sAbode_.Bmp");
	


	if (false == LevelPlayer->IsActorInBoundery())
	{
		MsgBoxAssert("Player가 맵의 제한위치에 설정되었습니다.");
		return;
	}





}

void EggCorridor_Cthulhu_sAbode::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	if (true == GameEngineInput::IsDown('J'))
	{
		MiddlePtr->SwitchRender();
	}
}


void EggCorridor_Cthulhu_sAbode::Release()
{
}


void EggCorridor_Cthulhu_sAbode::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}


	LevelPlayer->SetGroundTexture("EggCorridor-Cthulhu'sAbode_Col.Bmp");
	LevelPlayer->SetActorBoundery("EggCorridor-Cthulhu'sAbode_.Bmp");


	if (false == LevelPlayer->IsActorInBoundery())
	{
		MsgBoxAssert("Player가 맵의 제한위치에 설정되었습니다.");
		return;
	}




	
	

}

void EggCorridor_Cthulhu_sAbode::LevelEnd(GameEngineLevel* _NextLevel)
{

}