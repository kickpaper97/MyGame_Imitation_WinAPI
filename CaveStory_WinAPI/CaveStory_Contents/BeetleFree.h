
#pragma once
#include "Monster.h"

enum class HightDir
{
	Up,
	Down,
};

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


	float StartYPos = 0.0f;
	bool IsSetStartY = false;

	MonsterDir Dir = MonsterDir::Left;
	HightDir HDir = HightDir::Up;

	float4 MovePosX = float4::ZERO;
	float4 MovePosY = float4::ZERO;

	//float4 BodyCheckPos = LeftHeadCheck;
	//float4 HeadCheckPos = UpCheck;


	//float4 LeftBodyCheck = { -30.0f, -10.0f };
	//float4 RightBodyCheck = { 30.0f, -10.0f };
	//float4 LeftHeadCheck;
	//float4 RightHeadCheck;
	//float4 UpCheck = { 0.0f,-55.f };
};

