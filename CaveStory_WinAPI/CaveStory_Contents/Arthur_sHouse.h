
#pragma once
#include<GameEngineCore/GameEngineLevel.h>

class Arthur_sHouse : public GameEngineLevel
{
public:
	Arthur_sHouse();
	~Arthur_sHouse();

	Arthur_sHouse(const Arthur_sHouse& _Other) = delete;
	Arthur_sHouse(Arthur_sHouse&& _Other) noexcept = delete;
	Arthur_sHouse& operator=(const Arthur_sHouse& _Other) = delete;
	Arthur_sHouse& operator=(const Arthur_sHouse&& _Other) noexcept = delete;


protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:

	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	class BackGround* Ptr;

	class PlayerUIManager* PlayUI = nullptr;
	class Player* LevelPlayer = nullptr;
};

