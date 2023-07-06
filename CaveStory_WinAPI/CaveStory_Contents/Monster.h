
#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class MonsterSize
{
	Min,
	Mid,
	Max,
	None,
};

enum class MonsterDir
{
	Left,
	Right,
};

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

	

	void SetDamageValue(int _DamageValue)
	{
		DamageValue = _DamageValue;
	}

	int GetDamageValue() const
	{
		return DamageValue;
	}

	void SetPlayerPos(float4 _Pos)
	{
		PlayerPos = _Pos;
	}
	
	float4 GetPlayerPos() const
	{
		return PlayerPos;
	}

	void SetMonsterSize(MonsterSize _Size)
	{
		MonSize = _Size;
	}
	void SetMonsterSize(int _Size)
	{
		MonSize = static_cast<MonsterSize>(_Size);
	}

	int GetMonsterSize() const
	{
		return static_cast<int>(MonSize);
	}


	

	bool IsDamaged = false;

	void Drop();
	virtual void Damaged(float _Deltta);

protected:
	void Update(float _Delta) override;

	void Start() override;


	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineCollision* BodyCollision = nullptr;

	GameEngineSoundPlayer HurtSound;
	
private:

	float4 PlayerPos = {};
	MonsterSize MonSize = MonsterSize::None;

	int DamageValue = 2;

	static std::list<Monster*> AllMonster;


};

