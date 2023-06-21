
#pragma once
#include<GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class FieldEffect : public GameEngineActor
{
public:
	FieldEffect();
	~FieldEffect();

	FieldEffect(const FieldEffect& _Other) = delete;
	FieldEffect(FieldEffect&& _Other) noexcept = delete;
	FieldEffect& operator=(const FieldEffect& _Other) = delete;
	FieldEffect& operator=(const FieldEffect&& _Other) noexcept = delete;

	



	void SetRenderer(GameEngineRenderer* _Renderer)
	{
	
		Renderer = _Renderer;
	}
	void SetCollision(GameEngineCollision* _Collision)
	{
		Collision = _Collision;
	}


	void Update(float _Delta) override;

	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* Collision = nullptr;
protected:

private:
};

