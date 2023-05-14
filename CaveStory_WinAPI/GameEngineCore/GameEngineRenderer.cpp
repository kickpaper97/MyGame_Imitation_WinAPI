#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>
#include<GameEngineCore/GameEngineActor.h>
#include"GameEngineCamera.h"
#include "ResourcesManager.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);
	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐를 불러오려 시도했습니다." + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}

}
void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("이미지가 세팅이 안된 렌더러입니다");
	}
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos,CopyScale);
}


bool GameEngineRenderer::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}
