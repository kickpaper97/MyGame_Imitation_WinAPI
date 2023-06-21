
#pragma once
#include<GameEngineCore/GameEngineLevel.h>

class EggCorridor_Cthulhu_sAbode : public GameEngineLevel
{
public:
	EggCorridor_Cthulhu_sAbode();
	~EggCorridor_Cthulhu_sAbode();

	EggCorridor_Cthulhu_sAbode(const EggCorridor_Cthulhu_sAbode& _Other) = delete;
	EggCorridor_Cthulhu_sAbode(EggCorridor_Cthulhu_sAbode&& _Other) noexcept = delete;
	EggCorridor_Cthulhu_sAbode& operator=(const EggCorridor_Cthulhu_sAbode& _Other) = delete;
	EggCorridor_Cthulhu_sAbode& operator=(const EggCorridor_Cthulhu_sAbode&& _Other) noexcept = delete;


protected:
protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	class BackGround* MiddlePtr;

	class GameEngineRenderer* FrontGroundRenderer = nullptr;

	class Player* LevelPlayer = nullptr;
};



