
#pragma once
#include"Monster.h"

enum class CutterState
{
	Idle,
	Jump,
	Active,
	
};


class MonsterCutter : public Monster
{
public:
	MonsterCutter();
	~MonsterCutter();

	MonsterCutter(const MonsterCutter& _Other) = delete;
	MonsterCutter(MonsterCutter&& _Other) noexcept = delete;
	MonsterCutter& operator=(const MonsterCutter& _Other) = delete;
	MonsterCutter& operator=(const MonsterCutter&& _Other) noexcept = delete;

	void ChanageState(CutterState _State);
	void StateUpdate(float _Delta);

	void IdleStart();
	void JumpStart();
	void ActiveStart();

	void IdleUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void ActiveUpdate(float _Delta);

	std::string CurState = "";
	CutterState State = CutterState::Idle;
	MonsterDir Dir = MonsterDir::Left;

	void ChangeAnimationState(const std::string& _StateName);


protected:

private:
	void Start() override;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float4 PlayerDistance = {};

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

