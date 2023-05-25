#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	Jump_Arms,
	Play,
	Nomal_Arms,
	PlayUI,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
};