
#pragma once
#include "FieldEffect.h"


class LevelUp :public FieldEffect
{
public:
	LevelUp();
	~LevelUp();

	LevelUp(const LevelUp& _Other) = delete;
	LevelUp(LevelUp&& _Other) noexcept = delete;
	LevelUp& operator=(const LevelUp& _Other) = delete;
	LevelUp& operator=(const LevelUp&& _Other) noexcept = delete;

	void Start()override;
	void Update(float _Delta) override;
protected:

private:
	float4 CreatePos = {};
	float TimeCount = 0.0f;
};

