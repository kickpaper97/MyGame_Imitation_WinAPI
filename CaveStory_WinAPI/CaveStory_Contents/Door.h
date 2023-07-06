
#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>

class Door :public GameEngineActor
{
public:
	Door();
	~Door();

	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(const Door&& _Other) noexcept = delete;

	void Open()
	{
		Activate = true;
		MachineSound = GameEngineSound::SoundPlay("Door.wav");
	}
protected:

private:
	bool Activate = false;
	GameEngineRenderer* Renderer = nullptr;

	GameEngineSoundPlayer MachineSound;

	void Start() override;
	void Update(float _Delta) override;

};

