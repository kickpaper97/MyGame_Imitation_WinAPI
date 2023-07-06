
#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include<vector>

class GameEngineRenderer;
class PlayUIManager : public GameEngineActor
{
	
	friend class Player;

public:
	static PlayUIManager* UI;

	PlayUIManager();
	~PlayUIManager();

	PlayUIManager(const PlayUIManager& _Other) = delete;
	PlayUIManager(PlayUIManager&& _Other) noexcept = delete;
	PlayUIManager& operator=(const PlayUIManager& _Other) = delete;
	PlayUIManager& operator=(const PlayUIManager&& _Other) noexcept = delete;

	bool GetTextBoxIsUpdate();
	
	

	void TextBoxOn();
	
	void TextBoxOff();
	

	void ChoiceBoardOn();
	
	void ChoiceBoardOff();


protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	bool isUIChange = false;
	int PlayerLV = 0;

	std::vector<GameEngineRenderer*> PlayUI;
	

	GameEngineRenderer* CurHp = nullptr;
	GameEngineRenderer* CurLV = nullptr;
	GameEngineRenderer* CurExp = nullptr;


	float4 ExpBarScale;
	float4 ExpBarStartPos;

	float4 HPBarScale;
	float4 HPBarStartPos;


	GameEngineRenderer* TextBackGround = nullptr;
	GameEngineRenderer* ChoiceBoard = nullptr;
};

