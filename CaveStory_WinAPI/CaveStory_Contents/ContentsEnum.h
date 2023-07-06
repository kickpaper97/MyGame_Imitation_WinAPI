#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	BackPlay,
	MiddlePlay,
	FrontPlay,
	Bullet,
	FrontGround,
	UIBack,
	UIFront,

	
};

enum class CollisionOrder
{
	Map,
	Potal,
	Door,
	PlayerBody,
	MonsterBody,
	Bullet,
	ExpBall,
	CureMachine,
	Heart,
};