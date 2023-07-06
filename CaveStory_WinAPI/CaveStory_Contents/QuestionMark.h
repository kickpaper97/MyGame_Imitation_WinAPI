
#pragma once
#include "FieldEffect.h"

class QuestionMark :public FieldEffect
{
public:
	QuestionMark();
	~QuestionMark();

	QuestionMark(const QuestionMark& _Other) = delete;
	QuestionMark(QuestionMark&& _Other) noexcept = delete;
	QuestionMark& operator=(const QuestionMark& _Other) = delete;
	QuestionMark& operator=(const QuestionMark&& _Other) noexcept = delete;

	void Start()override;
	void Update(float _Delta)override;
protected:

private:
	float4 CreatePos = {};
	float TimeCount = 0.0f;
};

