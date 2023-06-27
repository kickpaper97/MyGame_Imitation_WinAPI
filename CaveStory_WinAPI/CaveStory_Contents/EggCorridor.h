
#pragma once

#include <GameEngineCore/GameEngineLevel.h>


class EggCorridor :public GameEngineLevel
{
public:
	EggCorridor();
	~EggCorridor();

	EggCorridor(const EggCorridor& _Other) = delete;
	EggCorridor(EggCorridor&& _Other) noexcept = delete;
	EggCorridor& operator=(const EggCorridor& _Other) = delete;
	EggCorridor& operator=(const EggCorridor&& _Other) noexcept = delete;


protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	class BackGround* MiddlePtr;


	class Player* LevelPlayer = nullptr;
};
