#pragma once
#include <Windows.h>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include"GameEngineWindowTexture.h"



class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(const GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	HDC GetHDC()
	{
		return Hdc;
	}

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	float4 GetMousePos();


	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	void ClearBackBuffer();
	void DoubleBuffering();


	static void WindowLoopOff()
	{
		IsWindowUpdate = false;
	}

	static bool IsFocus()
	{
		return IsFocusValue;
	}

protected:

private:
	static bool IsWindowUpdate;
	static bool IsFocusValue;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;

	float4 Scale;
	GameEngineWindowTexture* WindowBuffer = nullptr;
	GameEngineWindowTexture* BackBuffer = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};

