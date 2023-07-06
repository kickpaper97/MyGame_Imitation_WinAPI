
#pragma once
#include "Monster.h"

enum class BeetleState
{
	Idle,
	Move
};

class BeetleWall :public Monster
{
public:
	BeetleWall();
	~BeetleWall();

	BeetleWall(const BeetleWall& _Other) = delete;
	BeetleWall(BeetleWall&& _Other) noexcept = delete;
	BeetleWall& operator=(const BeetleWall& _Other) = delete;
	BeetleWall& operator=(const BeetleWall&& _Other) noexcept = delete;

	void ChanageState(BeetleState _State);
	void StateUpdate(float _Delta);

	void IdleStart();
	void MoveStart();

	void IdleUpdate(float _Delta);
	void MoveUpdate(float _Delta);

	std::string CurState = "";
	BeetleState State = BeetleState::Idle;
	MonsterDir Dir = MonsterDir::Left;

	void ChangeAnimationState(const std::string& _StateName);



protected:

private:

	void Start() override;

	void Update(float _Delta) override;
	void Render(float _Delta) override;
	

	float4 MovePos = float4::ZERO;

	float Waiting = 0.0f;

	float4 BodyCheckPos = LeftBodyCheck;
	


	float4 LeftBodyCheck = { -22.0f, 0.0f };
	float4 RightBodyCheck = { 22.0f, 0.0f };
};

