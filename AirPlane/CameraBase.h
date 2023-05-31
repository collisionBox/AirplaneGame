#pragma once
#include "DxLib.h"
class CameraBase
{
public:
	virtual void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex) = 0;// ������.
	virtual void Update(VECTOR pos, MATRIX matRot) = 0;  // �X�V����
	virtual void DebagDraw() {};

protected:
	void SetPos(const VECTOR set) { pos = set; }// �ʒu�Z�b�g

	VECTOR pos;// �ʒu�x�N�g��.
	VECTOR targetPos;// �����_�x�N�g��.
};

