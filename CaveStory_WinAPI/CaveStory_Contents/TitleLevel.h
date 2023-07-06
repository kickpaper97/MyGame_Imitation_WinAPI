
#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>



class TitleLevel :public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(const TitleLevel&& _Other) noexcept = delete;

	void Start();

protected:
	void Update(float _DeltaTime) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:

	int MenuSelect = 0;

	class BackGround* Select;
	 GameEngineSoundPlayer BGMPlayer ;
	 GameEngineSoundPlayer MenuSelectSound;

	

};

