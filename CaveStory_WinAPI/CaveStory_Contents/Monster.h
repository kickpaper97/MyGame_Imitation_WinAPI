
#pragma once
#include "PlayActor.h"


class Monster :public PlayActor
{
public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(const Monster&& _Other) noexcept = delete;

	static void AllMonsterDeath();

	void SetHp(const int _HP)
	{
		Hp = _HP;
	}
	int GetHp()
	{
		return Hp;
	}

protected:
	void Update(float _Delta) override;

	void Start() override;
private:

	int Hp = 100;

	static std::list<Monster*> AllMonster;


};

