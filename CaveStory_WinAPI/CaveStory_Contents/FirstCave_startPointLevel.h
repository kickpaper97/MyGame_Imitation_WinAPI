
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class FirstCave_StartPointLevel : public GameEngineLevel
{
public:
	FirstCave_StartPointLevel();
	~FirstCave_StartPointLevel();

	FirstCave_StartPointLevel(const FirstCave_StartPointLevel& _Other) = delete;
	FirstCave_StartPointLevel(FirstCave_StartPointLevel&& _Other) noexcept = delete;
	FirstCave_StartPointLevel& operator=(const FirstCave_StartPointLevel& _Other) = delete;
	FirstCave_StartPointLevel& operator=(const FirstCave_StartPointLevel&& _Other) noexcept = delete;


	
protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;
};

