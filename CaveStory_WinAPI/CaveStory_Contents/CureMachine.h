
#pragma once
#include<GameEngineCore/GameEngineActor.h>

class CureMachine :public GameEngineActor
{
public:
	CureMachine();
	~CureMachine();

	CureMachine(const CureMachine& _Other) = delete;
	CureMachine(CureMachine&& _Other) noexcept = delete;
	CureMachine& operator=(const CureMachine& _Other) = delete;
	CureMachine& operator=(const CureMachine&& _Other) noexcept = delete;


protected:

private:
	GameEngineSprite* Renderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

