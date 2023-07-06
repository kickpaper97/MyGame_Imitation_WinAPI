
#pragma once
#include<GameEngineCore/GameEngineActor.h>
#include<GameEnginePlatform/GameEngineSound.h>

class CureMachine :public GameEngineActor
{
public:
	CureMachine();
	~CureMachine();

	CureMachine(const CureMachine& _Other) = delete;
	CureMachine(CureMachine&& _Other) noexcept = delete;
	CureMachine& operator=(const CureMachine& _Other) = delete;
	CureMachine& operator=(const CureMachine&& _Other) noexcept = delete;

	void GetSound()
	{
		MachineSound = GameEngineSound::SoundPlay("health_refill.wav");
	}

protected:

private:
	GameEngineRenderer* Renderer = nullptr;

	GameEngineSoundPlayer MachineSound;

	void Start() override;
	void Update(float _Delta) override;
};

