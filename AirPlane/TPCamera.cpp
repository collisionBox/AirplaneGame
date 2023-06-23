#include "TPCamera.h"
void TPCamera::Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)
{
	this->pos = pos + ToZAxis(matRot) * OffsetX + ToYAxis(matRot) * OffsetY;
	targetPos = pos;
	dir = ToZAxis(matRot);
	dir.y = 0.0f;
	SetCameraPositionAndTarget_UpVecY(this->pos, targetPos);
}
void TPCamera::Update(VECTOR pos, MATRIX matRot, float deltaTime)
{
	targetPos = pos;
	VECTOR aimPos = targetPos + ToZAxis(matRot) * OffsetX;
	VECTOR posMoveDir = aimPos - this->pos;
	this->pos += posMoveDir * SpringStrength * deltaTime;
	this->pos.y = pos.y + OffsetY;

	if (!CheckHitKey(KEY_INPUT_C))
	{

	}
	SetCameraPositionAndTarget_UpVecY(this->pos, targetPos);

}

void TPCamera::Draw(VECTOR pos, MATRIX matRot,VECTOR velocity)
{
	
}

void TPCamera::DebagDraw()
{
	int white = GetColor(255, 255, 255);
}
