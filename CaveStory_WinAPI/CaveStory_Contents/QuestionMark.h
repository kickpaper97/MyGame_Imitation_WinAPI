
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

	void Start();
	void Update(float _Delta);
protected:

private:
	float4 CreatePos = {};
	float TimeCount = 0.0f;
};

