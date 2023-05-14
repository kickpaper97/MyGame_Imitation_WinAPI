#pragma once


// 설명 : 모든 기본적인 행동을 제안하는 클래스
// 제안하는 클래스

class GameEngineObject
{
	friend class GameEngineLevel;
public:
	GameEngineObject();
	~GameEngineObject();

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(const GameEngineObject&& _Other) noexcept = delete;


	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Render() {}
	virtual void Release() {}

	void On()
	{
		IsUpdateValue = true;
	}

	void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		IsDeathValue = true;
	}

	bool IsUpdate()
	{
		return true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}


protected:

private:

	bool IsUpdateValue = true;
	bool IsDeathValue = false;

	int Order = 0;
	float LiveTime = 0.0f;

	void AddLiveTime(float DeltaTime)
	{
		LiveTime += DeltaTime;
	}

};

