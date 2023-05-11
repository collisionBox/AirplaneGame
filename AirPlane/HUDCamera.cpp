#include "HUDCamera.h"
#include "Math.h"
HUDCamera::HUDCamera()
{
	Init();
}

HUDCamera::~HUDCamera()
{
}

void HUDCamera::Init()
{
	SetCameraPositionAndTarget_UpVecY(pos, targetPos);
}

void HUDCamera::Update(VECTOR pos, MATRIX matRot, float deltaTime)
{
	targetPos = pos;
	VECTOR targetDir = VNorm(ToZAxis(matRot));
	targetDir.y = 0;
	this->pos = targetDir * OffsetLen;
	pos.y = pos.y + OffsetY;
	SetCameraPositionAndTarget_UpVecY(this->pos, targetPos);
}
