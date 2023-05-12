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

void HUDCamera::Update(VECTOR pos, MATRIX matRot, float deltaTime)
{

	this->pos = pos + VNorm(ToZAxis(matRot)) * OffsetLen + VNorm(ToYAxis(matRot)) * OffsetY;
	targetPos = pos;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, VNorm(ToYAxis(matRot)));
	
}
