#pragma once
#include	 "DxLib.h"
#include "EffectTag.h"

class EffectBase
{
public:
	EffectBase(EffectTag tag);

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() {};

	bool GetValid() const { return valid; }
	EffectTag GetTag() const { return tag; }
protected:
	int handle;
	bool valid;// —LŒø‚©‚Ç‚¤‚©.
	EffectTag tag;



};

