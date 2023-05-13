
#pragma once
#include <GameEngineCore/GameEngineCore.h>

class ContentsCore :public CoreProcess
{
public:
	ContentsCore();
	~ContentsCore();

	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(const ContentsCore&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
protected:

private:

};

