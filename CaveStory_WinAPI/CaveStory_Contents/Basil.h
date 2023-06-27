
#pragma once
#include "Monster.h"

#define SpeedLimit 300.0f


class Basil : public Monster
{
public:
	Basil();
	~Basil();

	Basil(const Basil& _Other) = delete;
	Basil(Basil&& _Other) noexcept = delete;
	Basil& operator=(const Basil& _Other) = delete;
	Basil& operator=(const Basil&& _Other) noexcept = delete;


protected:

private:

	void Start() override;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	class GameEngineRenderer* Renderer = nullptr;
	
	float Speed = SpeedLimit;
	
	

	float4 BodyCheckPos = LeftHeadCheck;
	float4 HeadCheckPos = UpCheck;


	float4 LeftBodyCheck = { -30.0f, -10.0f };
	float4 RightBodyCheck = { 30.0f, -10.0f };
	float4 LeftHeadCheck;
	float4 RightHeadCheck;
	float4 UpCheck = { 0.0f,-55.f };
};

