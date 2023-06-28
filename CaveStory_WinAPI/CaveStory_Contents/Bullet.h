
#pragma once
#include<GameEngineCore/GameEngineActor.h>

enum class BulletDir
{
	Right,
	Left,
	Max,
};

enum class BulletLook
{
	Up,
	Middle,
	Down,
};

class Bullet :public GameEngineActor
{
public:
	Bullet();
	~Bullet();

	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(const Bullet&& _Other) noexcept = delete;

	



	template<typename EnumLook,typename EnumDir>
	void SetDir(const EnumLook& _Look, const EnumDir& _Dir) 
	{
		SetDir(static_cast<int>(_Look), static_cast<int>(_Dir));
	}

	void SetDir(const int _Look, const int _Dir);
	
	

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

	void SetDamage(const int _PLevel)
	{
		Level = _PLevel;
		return SetDamage();
	}



	void SetDamage()
	{
		switch (Level)
		{
		case 1:
			Damage = 1;
			break;

		case 2:
			Damage = 2;
			break;


		case 3:
			Damage = 4;
			break;

		default:
			MsgBoxAssert("플레이어의 레벨이 1~3이 아닙니다.");
			return;
			break;
		}
		
		
	}
	
	int GetDamage()
	{
		if (0 == Damage)
		{
			MsgBoxAssert("레벨에 따른 총알의 데미지가 설정되지 않았습니다.");
			return 0;
		}

		return Damage;
	}

	void SetLevel(const int _PLevel)
	{
		Level = _PLevel;
	}

protected:

private:
	int Damage = 0;
	int Level = 0;

	float4 Dir;
	float Speed = 1000.0f;

	GameEngineRenderer* Renderer = nullptr;
	GameEngineRenderer* EffectRenderer = nullptr;


	GameEngineCollision* BulletCollision = nullptr;
	GameEngineCollision* EffectCollision = nullptr;
	

	void Start() override;
	void Update(float _Delta) override;
	
};

