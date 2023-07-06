
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

	int GetExpValue() const
	{
		if (ExpValue == 0)
		{
			MsgBoxAssert("EXPball의 경험치 설정값이 0입니다");
			
		}

		return ExpValue;

	}
	

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineCollision* Collision = nullptr;

	float4 MovePos = float4::ZERO;
	
	

	int ExpValue = 0;
	
};

