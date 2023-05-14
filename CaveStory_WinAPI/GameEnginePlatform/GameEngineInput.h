
#pragma once
#include<Windows.h>
#include <GameEngineBase/GameEngineMath.h>
#include<map>

class GameEngineInput
{
private:
	class GameEngineKey 
	{
		friend GameEngineInput;

		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;


		float PressTime = 0.0f;

		int Key = -1;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Reset()
		{
			if (true == Press)
			{
				bool Down = false;
				bool Press = false;
				bool Up = true;
				bool Free = true;
			}
			else if (true == Up)
			{
				bool Down = false;
				bool Press = false;
				bool Up = false;
				bool Free = true;
			}
		}

		void Update(float _DeltaTime);
		

	public:
		GameEngineKey():Key(-1)
		{
		}

		GameEngineKey(int _Key):Key(_Key)
		{
		}
	};


public:
	GameEngineInput();
	~GameEngineInput();

	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(const GameEngineInput&& _Other) noexcept = delete;

	static float4 MousePos();

	static void InputInit();
	static void Update(float _DeltaTime);
	static void Reset();

	static bool IsDown(int _Key);
	static bool IsUp(int _Key);
	static bool IsPress(int _Key);
	static bool IsFree(int _Key);

protected:

private:
	static std::map<int, GameEngineKey> AllKeys;
};

