#include "Player.h"
#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{

	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}
void Player::Update(float _Delta)
{

	AddPos({ 100.0f * _Delta, 0.0f });
}
void Player::Render()
{


	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();

	Rectangle(WindowDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY()
	);

}
void Player::Release()
{

}