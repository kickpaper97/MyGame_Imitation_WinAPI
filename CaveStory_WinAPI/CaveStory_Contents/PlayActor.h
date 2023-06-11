
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayActor : public GameEngineActor
{
public:
	PlayActor();
	~PlayActor();

	PlayActor(const PlayActor& _Other) = delete;
	PlayActor(PlayActor&& _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor& _Other) = delete;
	PlayActor& operator=(const PlayActor&& _Other) noexcept = delete;

	void Gravity(float _Delta);

	void CameraFocus();


	void  GravityReset()
	{
		GravityVector = float4::ZERO;
	}


	void GravityOff()
	{
		IsGravity = false;
	}
	bool GetIsOnAir()
	{
		return IsGravity;
	}

	void SetGroundTexture(const std::string& _GroundTextureName);

	
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);


	float4 ActorCameraPos();

	float4 GetGravityVector() const
	{
		return GravityVector;
	}

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	void AddGravityVector(float4 _GravityVector)
	{
		GravityVector += _GravityVector;
	}

	
protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	


	bool IsGravity = true;


	float GravityPower = 1.0f;
	float4 GravityVector = float4::ZERO;
};

