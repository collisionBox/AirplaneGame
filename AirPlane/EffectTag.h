#pragma once

enum class EffectTag : unsigned char
{
	Graphic,
	Sound
};
constexpr static EffectTag EffectTagAll[] =
{
	EffectTag::Graphic,
	EffectTag::Sound,
};