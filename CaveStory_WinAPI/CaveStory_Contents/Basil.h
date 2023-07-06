
#pragma once
#include "Monster.h"

#define SpeedLimit 5.0f



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
	

	
	float Speed = SpeedLimit;

	MonsterDir Dir = MonsterDir::Left;
	float4 MovePos = float4::ZERO;
	

	float4 BodyCheckPos = LeftBodyCheck;
	


	float4 LeftBodyCheck = { -16.0f, -10.0f };
	float4 RightBodyCheck = { 16.0f,-10.0f };
	
	
};

