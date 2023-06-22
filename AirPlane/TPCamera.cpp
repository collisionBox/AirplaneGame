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
	aimDir.y = 0;// •½–Ê‚Æ‚µ‚ÄŒvŽZ‚·‚é‚½‚ß.
	float angle = FormedAngle(VGet(dir.x, 0, dir.z), aimDir);
	if(angle > 0)
	{
		if (angle <= ToRadian(MaxAngle))
		{
			dir = RotateForAimVecYAxis(VGet(dir.x, 0, dir.z), aimDir, angle);
		}
		else
		{
			VECTOR preDir = RotateForAimVecYAxis(aimDir,VGet(dir.x, 0, dir.z), MaxAngle);
			dir.x = preDir.x;
			dir.z = preDir.z;
		}

		if (angle < Epsilon)
		{
			dir.x = aimDir.x;
			dir.z = aimDir.z;
		}
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
