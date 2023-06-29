
#pragma once
#include"PlayActor.h"

enum class BallType
{
	Min,
	Mid,
	Max,
	None,
};

class ExpBall :public PlayActor
{
public:
	ExpBall();
	~ExpBall();

	ExpBall(const ExpBall& _Other) = delete;
	ExpBall(ExpBall&& _Other) noexcept = delete;
	ExpBall& operator=(const ExpBall& _Other) = delete;
	ExpBall& operator=(const ExpBall&& _Other) noexcept = delete;

	template<typename BallType>
	void SetBallType(BallType _Type)
	{
		return SetBallType(static_cast<int>(_Type));
	}

	void SetBallType(const int _Type);

	
	

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineCollision* Collision = nullptr;
};

