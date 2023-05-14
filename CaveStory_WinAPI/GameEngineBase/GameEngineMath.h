
#pragma once

class GameEngineMath
{
};

class float4
{

public:


	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	float X=0.0f;
	float Y=0.0f;
	float Z=0.0f;
	float W=0.0f;

	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline float hX() const
	{
		return 0.5f * X;
	}

	inline float hY() const
	{
		return 0.5f * Y;
	}

	inline int ihX() const
	{
		return static_cast<int>(hX());
	}

	inline int ihY() const
	{
		return static_cast<int>(hY());
	}

	inline float4 Half() const 
	{
		return { hX(),hY(),Z,W};
	}

	float4& operator+=(const float4 _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4& operator-=(const float4 _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}
	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	float4& operator*=(const float4 _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4 operator+(const float4 _Other)
	{
		float4 ReturnValue;
		ReturnValue.X =X + _Other.X;
		ReturnValue.Y =Y + _Other.Y;
		ReturnValue.Z =Z + _Other.Z;

		return ReturnValue;
	}

	float4 operator-()
	{
		float4 ReturnValue = *this;
		ReturnValue.X = -X;
		ReturnValue.Y = -Y;
		ReturnValue.Z = -Z;

		return ReturnValue;
	}

	float4 operator-(const float4 _Other)
	{
		float4 ReturnValue;
		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}
	float4 operator*(const float4 _Other)
	{
		float4 ReturnValue;
		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float _Value)
	{
		float4 ReturnValue;
		ReturnValue.X = X *_Value;
		ReturnValue.Y = Y *_Value;
		ReturnValue.Z = Z *_Value;

		return ReturnValue;
	}
private:

};

