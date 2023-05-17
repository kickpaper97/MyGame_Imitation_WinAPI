
#pragma once
#include "GameEngineObject.h"
#include<GameEngineBase/GameEngineMath.h>
#include<string>
#include <map>
#include <vector>


class GameEngineSprite;
class GameEngineActor;
class GameEngineWindowTexture;
class GameEngineRenderer :public GameEngineObject
{
	friend class GameEngineCamera;
	friend class GameEngineActor;

public:
	GameEngineRenderer();
	~GameEngineRenderer();

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

	void SetSprite(const std::string& _Name, size_t _index = 0);

	void SetTexture(const std::string& _Name);

	void SetRenderPos(const float4& _Value)
	{
		RenderPos = _Value;
	}


	void SetRenderScale(const float4& _Value)
	{
		RenderScale = _Value;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Value)
	{
		CopyPos = _Value;
	}
	void SetCopyScale(const float4& _Value)
	{
		CopyScale = _Value;
	}

	void SetRenderScaleToTexture();

	bool IsDeath() override;


	void SetScaleRatio(const float& _Scale)
	{
		ScaleRatio = _Scale;
	}

	

protected:

private:
	GameEngineActor* Master = nullptr;
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineSprite* Sprite = nullptr;


	float ScaleRatio = 1.0f;
	bool ScaleCheck = false;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;

	void Render(class GameEngineCamera* _Camera,float _DeltaTime);

	class Animation
	{
	public:
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		std::vector <float> Inters ;
		bool Loop = true;
	};

public:
	Animation* FindAnimation(const std::string& _AnimationName);

	void CreateAnimation(
		const std::string& _AnimationName,
		const std::string& _SpriteName,
		size_t _Start = -1, size_t _End = -1,
		float _Inter = 0.1f,
		bool _LOOP = true);

	void ChangeAnimation(const std::string& _AnimationName, bool _ForceChange = false);

	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
};

