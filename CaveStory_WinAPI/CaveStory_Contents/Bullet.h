
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

	class GameEngineRenderer* Renderer=nullptr;
	class GameEngineCollision* BulletCollision = nullptr;

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

protected:

private:
	float4 Dir;
	float Speed = 1000.0f;

	

	void Start() override;
	void Update(float _Delta) override;
	
};

