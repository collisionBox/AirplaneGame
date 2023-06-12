#include "TPCamera.h"
#include "Math.h"
void TPCamera::Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)
{
	this->pos = pos + VNorm(ToZAxis(matRot)) * OffsetX + VNorm(ToYAxis(matRot)) * OffsetY;
	targetPos = pos;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, VNorm(ToYAxis(matRot)));
}

void TPCamera::Update(VECTOR pos, MATRIX matRot)
{
	VECTOR upVec = VGet(0.0f, 1.0f, 0.0f);
	if (!CheckHitKey(KEY_INPUT_C))
	{
		this->pos = pos + VNorm(ToZAxis(matRot)) * OffsetLen + VNorm(ToYAxis(matRot)) * OffsetY;
		upVec = VNorm(ToYAxis(matRot));
	}
	targetPos = pos;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, upVec);
}

void TPCamera::Draw(VECTOR pos, MATRIX matRot)
{
	
}

void TPCamera::DebagDraw()
{
}
