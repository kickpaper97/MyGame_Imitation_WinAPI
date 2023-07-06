
#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define NomalGravityPower 1.8f

class GameEngineWindowTexture;
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

	void SetGroundTexture(const std::string& _GroundTextureName);
	void SetGroundTexture(GameEngineWindowTexture* _GroundTexture);

	GameEngineWindowTexture* GetGroundTexture() const
	{
		
		return GroundTexture;
	}
	

	
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

	void SetActorBoundery(const std::string& _BounderyTextureName);

	bool IsActorInBoundery()
	{
		if (GetPos().X> Boundery.X)
		{
			return false;
		}
		if (GetPos().X < 0.0f)
		{
			return false;
		}
		if (GetPos().Y < 0.0f)
		{
			return false;
		}
		if (GetPos().Y > Boundery.Y)
		{
			return false;
		}

			return true;
	}

	void SetHp(const int _HP)
	{
		HP = _HP;
	}
	int GetHp()
	{
		return HP;
	}

	void SetGravityPower(float _GravityPower)
	{
		GravityPower = _GravityPower;
	}

	
protected:
	

private:
	GameEngineWindowTexture* GroundTexture = nullptr;
	GameEngineWindowTexture* BounderyTexture = nullptr;

	float4 Boundery = float4::ZERO;

	int HP = 0;
	
	bool IsGravity = true;

	float GravityPower = 1.8f;
	float4 GravityVector = float4::ZERO;

};

