
#pragma once

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
class EndingLevel :public GameEngineLevel
{
public:
	EndingLevel();
	~EndingLevel();

	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(const EndingLevel&& _Other) noexcept = delete;

	void Start();
protected:
	void Update(float _DeltaTime) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
private:
	GameEngineSoundPlayer BGMPlayer;

};

