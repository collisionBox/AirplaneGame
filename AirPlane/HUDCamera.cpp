#include "HUDCamera.h"
#include "Math.h"
HUDCamera::HUDCamera()
{
}

HUDCamera::~HUDCamera()
{
}

void HUDCamera::Init(VECTOR pos, MATRIX matRot)
{
	this->pos = pos + VNorm(ToZAxis(matRot)) * OffsetLen + VNorm(ToYAxis(matRot)) * OffsetY;
	targetPos = pos;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, VNorm(ToYAxis(matRot)));
}

void HUDCamera::Update(VECTOR pos, MATRIX matRot, float modelScale, float deltaTime)
{
#if 1
	VECTOR upVec = VGet(0.0f, 1.0f, 0.0f);
	if (!CheckHitKey(KEY_INPUT_C))
	{
		this->pos = pos + VNorm(ToZAxis(matRot)) * OffsetLen + VNorm(ToYAxis(matRot)) * OffsetY;
		upVec = VNorm(ToYAxis(matRot));
	}
	targetPos = pos;
#else
	this->pos = pos;
	this->pos += VNorm(ToYAxis(matRot))* Cockpit.y * modelScale;
	this->pos += VNorm(ToZAxis(matRot)) * Cockpit.z * modelScale;
	targetPos = VNorm(ToZAxis(matRot)) * -OffsetLen;
#endif
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, upVec);
	
}
