#pragma once

enum class ObjectTag : unsigned char
{
	Player,
	Enemy,
	Bullet,
	Camera,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::Enemy,
	ObjectTag::Bullet,
	ObjectTag::Camera,
};

