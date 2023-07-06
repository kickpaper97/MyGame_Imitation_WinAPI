
#pragma once
#include "PlayActor.h"
#include<GameEnginePlatform/GameEngineSound.h>

#define MaxEXP 16
#define MaxHp 16

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Hover,
	Search,
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

enum class Weapon
{
	MorningStar,
	Missile,

};

class Player : public PlayActor
{ 

	friend class ExpBall;
	friend class PlayUIManager;
	
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(const Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* ArmRenderer = nullptr;
	
	//GameEngineRenderer* BulletEffect=nullptr;

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
	void SearchStart();

	// 클래스로 만들어도 되고.
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void HoverUpdate(float _Delta);
	void SearchUpdate(float _Delta);

	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Right;
	PlayerLook Look = PlayerLook::Middle;
	std::string CurState = "";

	void DirCheck();


	void ChangeAnimationState(const std::string& _StateName);

	void SetExp(int _Exp)
	{
		Exp = _Exp;
	}

	int GetExp() const
	{
		return Exp;
	}

	void SetPlayerLV(int _LV)
	{
		PlayerLevel = _LV;
	}

	int GetPlayerLV() const
	{
		return PlayerLevel;
	}

private:
	
	
	int Exp = 5;
	int PlayerLevel = 1;

	bool CanHover = true;
	bool CanSearch = true;
	bool isDamage = false;
	float4 MovePos = float4::ZERO;
	float4 BodyCheckPos = LeftHeadCheck;
	float4 HeadCheckPos = UpCheck;

	float deltacheck = 0.0f;
	

	GameEngineCollision* BodyCollision = nullptr;

	bool DebugMode = false;
	bool GodMode = false;

	GameEngineSoundPlayer ShootSound;
	GameEngineSoundPlayer PlayerSound;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelStart() override;
		
	static Player* MainPlayer;

	float4 LeftBodyCheck = { -20.0f, -10.0f };
	float4 RightBodyCheck = { 20.0f, -10.0f };
	float4 LeftHeadCheck;
	float4 RightHeadCheck;
	float4 UpCheck = { 0.0f,-62.f };

};

