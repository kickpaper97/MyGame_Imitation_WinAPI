
#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

class BackGround : public GameEngineActor
{
public:
	BackGround();
	~BackGround();

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, const float _ScaleRatio = 1);

	void Init(const std::string& _FileName, const std::string& _DebugFileName,const float _scaleRatio=1);

	//float4 GetBackGroundScale() const;
	


	void SwitchRender();

protected:

	

private:
	bool IsNeedBackGroundDebug = true;
	
	bool SwitchRenderValue = true;

	std::string FileName;
	class GameEngineRenderer* Renderer;
	class GameEngineRenderer* DebugRenderer;

	//float4 Scale = float4::ZERO;


	void Start() override;
	void Update(float _Delta) override;
	
	void Release() override;
};

