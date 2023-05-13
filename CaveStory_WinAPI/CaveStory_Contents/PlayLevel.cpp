#include "PlayLevel.h"
#include"Player.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	CreatorActor<Player>();
}

void PlayLevel::Update(float _Delta)
{
}

void PlayLevel::Render()
{
}

void PlayLevel::Release()
{
}
