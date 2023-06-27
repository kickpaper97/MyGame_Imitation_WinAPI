#include "PlayUIManager.h"
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


		}


		{
			 HPBar = CreateUIRenderer("HPBar.bmp", RenderOrder::FrontPlay);
			HPBar->SetRenderPos({ 180, 150 });
			HPBar->SetTexture("HPBar.bmp");
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

	if (TextBackGround->IsUpdate())
	{
		HPBar->Off();
	}
	else
	{
		HPBar->On();
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