#include "PlayUIManager.h"
#include "Player.h"

#include"ContentsEnum.h"


#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>

PlayUIManager* PlayUIManager::UI = nullptr;

PlayUIManager::PlayUIManager()
{
	UI = this;
}

PlayUIManager::~PlayUIManager()
{
}

void PlayUIManager::Start()
{
	////HPBar
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("HPBar.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("Resources");
			FilePath.MoveChild("Resources\\Texture\\");
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.Bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CurHp.Bmp"));



		}


		{
			GameEngineRenderer* HPBar = CreateUIRenderer("HPBar.bmp", RenderOrder::UIBack);
			HPBar->SetRenderPos({ 180, 150 });
			PlayUI.push_back(HPBar);
		}

		{
			GameEngineWindowTexture* texure = ResourcesManager::GetInst().FindTexture("CurHp.Bmp");

			HPBarScale = texure->GetScale();
			CurHp= CreateUIRenderer("CurHp.bmp", RenderOrder::UIFront);
			
			CurHp->SetRenderPos({ 226.5f, 147 });
			HPBarStartPos = CurHp->GetRenderPos();
			PlayUI.push_back(CurHp);

		}




		if (false == ResourcesManager::GetInst().IsLoadTexture("ExpBar.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("Resources");
			FilePath.MoveChild("Resources\\Texture\\");
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ExpBar.Bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CurExp.Bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ExpMax.Bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LVText.Bmp"));

			
			
		}

		

		{
			GameEngineRenderer* LVText = CreateUIRenderer("LVText.bmp", RenderOrder::UIBack);
			LVText->SetRenderPos({ 75, 115 });
			PlayUI.push_back(LVText);
		}
		{
			GameEngineWindowTexture* texure = ResourcesManager::GetInst().FindTexture("CurExp.Bmp");

			ExpBarScale = texure->GetScale();
			GameEngineRenderer* ExpBar = CreateUIRenderer("ExpBar.bmp", RenderOrder::UIBack);
			ExpBar->SetRenderPos({ 228, 115 });
			PlayUI.push_back(ExpBar);
		}

		{
			CurExp = CreateUIRenderer("CurExp.bmp", RenderOrder::UIFront);
			//CurExp->SetTexture("ExpMax.Bmp");

			CurExp->SetRenderPos({ 226.5f, 112 });
			ExpBarStartPos = CurExp->GetRenderPos();
			PlayUI.push_back(CurHp);

		}

		

	}



	if (false == ResourcesManager::GetInst().IsLoadTexture("Number.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Number.Bmp"), 11, 2);

	}
	{
		CurLV = CreateUIRenderer(RenderOrder::UIBack);
		CurLV->CreateAnimation("1", "Number.Bmp", 1, 1, 0.1f, false);
		CurLV->CreateAnimation("2", "Number.Bmp", 2 ,2, 0.1f, false);
		CurLV->CreateAnimation("3", "Number.Bmp", 3, 3, 0.1f, false);
		CurLV->ChangeAnimation("1");
		CurLV->SetRenderPos({ 130, 115 });
		PlayUI.push_back(CurLV);

		PlayerLV = Player::GetMainPlayer()->GetPlayerLV();
		CurLV->ChangeAnimation(std::to_string(PlayerLV));
		
	}

	{



		if (false == ResourcesManager::GetInst().IsLoadTexture("ArmImage.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("Resources");
			FilePath.MoveChild("Resources\\Texture\\");
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ArmImage.Bmp"));
			

		}


		{
			GameEngineRenderer* ArmImage = CreateUIRenderer("ArmImage.bmp", RenderOrder::UIBack);
			ArmImage->SetRenderPos({ 81, 70});
			PlayUI.push_back(ArmImage);
		}



	}


	///TextBackGround
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("TextBox.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("Resources");
			FilePath.MoveChild("Resources\\Texture\\");
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TextBox.Bmp"));


		}


		{
			float4 WinScale = GameEngineWindow::MainWindow.GetScale();
			float4 Pos = { WinScale.hX() ,WinScale.Y - WinScale.hY() / 4.0f-10.0f };
			TextBackGround = CreateUIRenderer("TextBox.bmp", RenderOrder::MiddlePlay);
			TextBackGround->SetRenderPos(Pos);
			//TextBackGround->SetRenderScale({ 40, 40 });
			TextBackGround->SetTexture("TextBox.bmp");
			TextBackGround->Off();
		}
	}
		///ChoicBox
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("Choice.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("Resources");
			FilePath.MoveChild("Resources\\Texture\\");
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Choice.Bmp"));


		}


		{
			float4 WinScale = GameEngineWindow::MainWindow.GetScale();
			float4 Pos = { WinScale.X-(WinScale.hX()/3.0f) ,WinScale.Y - WinScale.hY() / 1.5f + 15.0f };
			ChoiceBoard = CreateUIRenderer("Choice.bmp", RenderOrder::MiddlePlay);
			ChoiceBoard->SetRenderPos(Pos);
			//TextBackGround->SetRenderScale({ 40, 40 });
			ChoiceBoard->SetTexture("Choice.bmp");
			ChoiceBoard->Off();

		}
	}



}

bool PlayUIManager::GetTextBoxIsUpdate()
{
	return TextBackGround->IsUpdate();
}

void PlayUIManager::Update(float _Delta)
{

	
	PlayerLV = Player::GetMainPlayer()->GetPlayerLV();
	CurLV->ChangeAnimation(std::to_string(PlayerLV));

	
	{
		if (3 == PlayerLV)
		{
			CurExp->SetTexture("ExpMax.Bmp");
			CurExp->SetRenderPos(ExpBarStartPos);
			CurExp->SetRenderScale(ExpBarScale);
		}
		else
		{
			CurExp->SetTexture("CurExp.Bmp");
			float check = Player::GetMainPlayer()->GetExp() * (ExpBarScale.X / MaxEXP);
			CurExp->SetRenderScale({ check,ExpBarScale.Y });
			
			float Checkx = ExpBarStartPos.X - ((MaxEXP - (float)Player::GetMainPlayer()->GetExp() ) * ExpBarScale.hX()/MaxEXP);

			CurExp->SetRenderPos({ Checkx,ExpBarStartPos.Y});

		}
	}



	{
		
		float check = Player::GetMainPlayer()->GetHp() * (HPBarScale.X / MaxHp);
		CurHp->SetRenderScale({ check,HPBarScale.Y });

		float Checkx = HPBarStartPos.X - ((MaxEXP - (float)Player::GetMainPlayer()->GetHp()) * HPBarScale.hX() / MaxHp);

		CurHp->SetRenderPos({ Checkx,HPBarStartPos.Y });

	}


	if (GetTextBoxIsUpdate())
	{
		for (GameEngineRenderer* CurUI : PlayUI)

		{
			GameEngineRenderer* UI = CurUI;
			if (true == UI->IsUpdate())
			{
				UI->Off();

			}

			continue;

		}

	}
	else
	{
		for (GameEngineRenderer* CurUI : PlayUI)

		{
			GameEngineRenderer* UI = CurUI;
			if (false == UI->IsUpdate())
			{
				UI->On();

			}

			continue;

		}
	}
}



void PlayUIManager::TextBoxOn()
{
	TextBackGround->On();
}
void PlayUIManager::TextBoxOff()
{
	TextBackGround->Off();
}

void PlayUIManager::ChoiceBoardOn()
{
	ChoiceBoard->On();
}
void PlayUIManager::ChoiceBoardOff()
{
	ChoiceBoard->Off();
}