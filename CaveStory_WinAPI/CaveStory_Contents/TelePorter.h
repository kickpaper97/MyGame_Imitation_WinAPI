
#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>

class TelePorter :public GameEngineActor
{
public:
	TelePorter();
	~TelePorter();

	TelePorter(const TelePorter& _Other) = delete;
	TelePorter(TelePorter&& _Other) noexcept = delete;
	TelePorter& operator=(const TelePorter& _Other) = delete;
	TelePorter& operator=(const TelePorter&& _Other) noexcept = delete;

	void SetDestination(const std::string& _Destinaiton)
	{
		Destination = _Destinaiton;
	}
	
	void Teleport();
	

protected:

private:
	bool Activate = false;
	GameEngineRenderer* Renderer = nullptr;
	GameEngineRenderer* LightRenderer = nullptr;
	
	
	std::string Destination = "";

	GameEngineSoundPlayer MachineSound;

	void Start() override;
	void Update(float _Delta) override;

};

