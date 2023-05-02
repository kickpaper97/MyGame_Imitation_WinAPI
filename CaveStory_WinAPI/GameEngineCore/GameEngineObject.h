#pragma once


// 설명 : 모든 기본적인 행동을 제안하는 클래스
// 제안하는 클래스

class GameEngineObject
{
public:
	GameEngineObject();
	~GameEngineObject();

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(const GameEngineObject&& _Other) noexcept = delete;


	virtual void Start() {}
	virtual void Update() {}
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

	bool IsDeath()
	{
		return IsDeathValue;
	}


protected:

private:

	bool IsUpdateValue = true;
	bool IsDeathValue = false;

};

