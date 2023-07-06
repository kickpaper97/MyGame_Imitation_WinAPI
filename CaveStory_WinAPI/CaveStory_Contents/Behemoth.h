
#pragma once
#include "Monster.h"

enum class BehemothState
{
	
	Move,
	Anger,
	Damaged,
	
};

class Behemoth :public Monster
{
public:
	Behemoth();
	~Behemoth();

	Behemoth(const Behemoth& _Other) = delete;
	Behemoth(Behemoth&& _Other) noexcept = delete;
	Behemoth& operator=(const Behemoth& _Other) = delete;
	Behemoth& operator=(const Behemoth&& _Other) noexcept = delete;

	void ChanageState(BehemothState _State);
	void StateUpdate(float _Delta);

	void MoveStart();
	void AngerStart();
	void DamagedStart();


	void MoveUpdate(float _Delta);
	void AngerUpdate(float _Delta);
	void DamagedUpdate(float _Delta);


	std::string CurState = "";
	BehemothState State = BehemothState::Move;
	MonsterDir Dir = MonsterDir::Left;

	void ChangeAnimationState(const std::string& _StateName);


protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float4 MovePos = float4::ZERO;


	float4 BodyCheckPos = LeftBodyCheck;
	


	float4 LeftBodyCheck = { -56.0f, -10.0f };
	float4 RightBodyCheck = { 56.0f, -10.0f };
	
};

