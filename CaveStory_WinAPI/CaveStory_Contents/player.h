
#pragma once
#include "PlayActor.h"


enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Hover,
	Max,
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

enum class PlayerLook
{
	Up,
	Middle,
	Down,
};

class Player : public PlayActor
{ 
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(const Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* ArmRenderer = nullptr;

	static Player* GetMainPlayer() 
	{
		return MainPlayer;
	}


protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();
	void JumpStart();
	void HoverStart();

	// 클래스로 만들어도 되고.
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void HoverUpdate(float _Delta);

	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Right;
	PlayerLook Look = PlayerLook::Middle;
	std::string CurState = "";

	void DirCheck();


	void ChangeAnimationState(const std::string& _StateName);


private:
	float JumpPower = 0.0f;
	int Exp = 0;
	int PlayerLevel = 1;

	bool CanHover = true;
	float4 MovePos = float4::ZERO;
	float4 CheckPos = UpCheck;

	float deltacheck = 0.0f;

	GameEngineCollision* BodyCollision = nullptr;


	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelStart() override;
		
	static Player* MainPlayer;

	float4 LeftCheck = { -20.0f, -50.0f };
	float4 RightCheck = { 20.0f, -50.0f };
	float4 UpCheck = { 0.0f,-64.f };

};

