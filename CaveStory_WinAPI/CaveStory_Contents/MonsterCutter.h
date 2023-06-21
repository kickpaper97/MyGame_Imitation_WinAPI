
#pragma once
#include"Monster.h"

class MonsterCutter : public Monster
{
public:
	MonsterCutter();
	~MonsterCutter();

	MonsterCutter(const MonsterCutter& _Other) = delete;
	MonsterCutter(MonsterCutter&& _Other) noexcept = delete;
	MonsterCutter& operator=(const MonsterCutter& _Other) = delete;
	MonsterCutter& operator=(const MonsterCutter&& _Other) noexcept = delete;


protected:

private:
	void Start() override;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	class GameEngineRenderer* Renderer = nullptr;

	bool CanMove = true;
	float MoveReLoad = 1.0f;

	float4 BodyCheckPos = LeftHeadCheck;
	float4 HeadCheckPos = UpCheck;


	float4 LeftBodyCheck = { -30.0f, -10.0f };
	float4 RightBodyCheck = { 30.0f, -10.0f };
	float4 LeftHeadCheck;
	float4 RightHeadCheck;
	float4 UpCheck = { 0.0f,-55.f };
};

