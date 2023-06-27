
#pragma once
#include "Monster.h"

class BeetleFree : public Monster
{
public:
	BeetleFree();
	~BeetleFree();

	BeetleFree(const BeetleFree& _Other) = delete;
	BeetleFree(BeetleFree&& _Other) noexcept = delete;
	BeetleFree& operator=(const BeetleFree& _Other) = delete;
	BeetleFree& operator=(const BeetleFree&& _Other) noexcept = delete;


protected:

private:


	void Start() override;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	class GameEngineRenderer* Renderer = nullptr;





	float4 BodyCheckPos = LeftHeadCheck;
	float4 HeadCheckPos = UpCheck;


	float4 LeftBodyCheck = { -30.0f, -10.0f };
	float4 RightBodyCheck = { 30.0f, -10.0f };
	float4 LeftHeadCheck;
	float4 RightHeadCheck;
	float4 UpCheck = { 0.0f,-55.f };
};

