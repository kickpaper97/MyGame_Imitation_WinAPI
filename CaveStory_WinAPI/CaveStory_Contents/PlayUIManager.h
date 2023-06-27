
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class PlayUIManager : public GameEngineActor
{
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

	GameEngineRenderer* HPBar = nullptr;
	GameEngineRenderer* TextBackGround = nullptr;
	GameEngineRenderer* ChoiceBoard = nullptr;
};

