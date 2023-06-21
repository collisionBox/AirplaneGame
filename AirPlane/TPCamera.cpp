#include "TPCamera.h"
void TPCamera::Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)
{
	this->pos = pos + ToZAxis(matRot) * OffsetX + ToYAxis(matRot) * OffsetY;
	targetPos = pos;
	dir = ToZAxis(matRot);
	dir.y = 0.0f;
	SetCameraPositionAndTarget_UpVecY(this->pos, targetPos);
}
// �@��pos�𒆐S�Ƃ������aOffsetLen�̉~�^��
// �������̂��������z���ʂ̕����Ƃ��ď���������
// �������Ɨ\������̊Ԃ̊p�x���Z�o
// 
//
void TPCamera::Update(VECTOR pos, MATRIX matRot)
{
	//if (!CheckHitKey(KEY_INPUT_C))
//{
//	
//}


	targetPos = pos;
	VECTOR aimDir = ToZAxis(matRot);
	aimDir.y = 0;
	float dot = VDot(VGet(dir.x, 0, dir.z), aimDir);
	//if (dot < 0.99)
	if(!IsNearAngle(VGet(dir.x, 0, dir.z), aimDir))
	{
		dir = RotateForAimVecYAxis(VGet(dir.x, 0, dir.z), aimDir, 10);

	}
	else
	{
		
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
}
