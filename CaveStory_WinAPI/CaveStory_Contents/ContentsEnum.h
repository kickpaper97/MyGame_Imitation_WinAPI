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
	
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
	Bullet,
};