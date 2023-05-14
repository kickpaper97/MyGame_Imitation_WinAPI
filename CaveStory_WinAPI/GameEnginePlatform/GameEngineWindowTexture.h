
#pragma once
#include <Windows.h>
#include<string>
#include<GameEngineBase/GameEngineMath.h>


class GameEngineWindowTexture
{
public:
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);
	void ResCreate(HDC _ImageDC)
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);




	float4 GetScale();

	HDC GetImageDC()
	{
		return ImageDC;
	}

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4 _Scale);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 0, 255));

	

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	BITMAP Info;

	void ScaleCheck();
};

