
#pragma once
#include "PlayActor.h"


class Monster :public PlayActor
{

	friend class GameEngineLevel;
public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(const Monster&& _Other) noexcept = delete;

	static void AllMonsterDeath();
	static void MonsterBoundaryCheck();

	void SetHp(const int _HP)
	{
		Hp = _HP;
	}
	int GetHp()
	{
		return Hp;
	}

	void SetPlayerPos(float4 _Pos)
	{
		PlayerPos = _Pos;
	}
	
	float4 GetPlayerPos() const
	{
		return PlayerPos;
	}


protected:
	void Update(float _Delta) override;

	void Start() override;
	void Release() override;

	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineCollision* BodyCollision = nullptr;
	
private:

	float4 PlayerPos;

	int Hp ;

	static std::list<Monster*> AllMonster;


};

