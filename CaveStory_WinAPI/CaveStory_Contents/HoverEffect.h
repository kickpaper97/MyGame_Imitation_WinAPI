
#pragma once
#include"FieldEffect.h"

class HoverEffect :public FieldEffect
{
public:
	HoverEffect();
	~HoverEffect();

	HoverEffect(const HoverEffect& _Other) = delete;
	HoverEffect(HoverEffect&& _Other) noexcept = delete;
	HoverEffect& operator=(const HoverEffect& _Other) = delete;
	HoverEffect& operator=(const HoverEffect&& _Other) noexcept = delete;

	void Start();
protected:

private:

};

