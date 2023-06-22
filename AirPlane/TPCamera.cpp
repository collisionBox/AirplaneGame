#include "TPCamera.h"
void TPCamera::Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)
{
	this->pos = pos + ToZAxis(matRot) * OffsetX + ToYAxis(matRot) * OffsetY;
	targetPos = pos;
	dir = ToZAxis(matRot);
	dir.y = 0.0f;
	SetCameraPositionAndTarget_UpVecY(this->pos, targetPos);
}
void TPCamera::Update(VECTOR pos, MATRIX matRot)
{
	if (!CheckHitKey(KEY_INPUT_C))
	{
	
	}


	targetPos = pos;
	VECTOR aimDir = ToZAxis(matRot);
	aimDir.y = 0;
	float dot = VDot(VGet(dir.x, 0, dir.z), aimDir);
	float angle = FormedAngle(VGet(dir.x, 0, dir.z), aimDir);
	valiable = angle;
	if(angle > 0)
	{
		dir = RotateForAimVecYAxis(VGet(dir.x, 0, dir.z), aimDir, angle);

	}
	this->pos = dir * OffsetLen;
	this->pos.y = OffsetY;
	SetCameraPositionAndTarget_UpVecY(this->pos, targetPos);

}

void TPCamera::Draw(VECTOR pos, MATRIX matRot,VECTOR velocity)
{
	
}

void TPCamera::DebagDraw()
{
	int white = GetColor(255, 255, 255);
	DrawFormatString(10, 100, white, "%f", valiable);
}
