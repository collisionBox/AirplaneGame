#pragma once
#include "DxLib.h"
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Init() = 0;
	virtual void Update(VECTOR pos, MATRIX matRot, float deltaTime) = 0;  // �Q�[���I�u�W�F�N�g�X�V����

protected:
	void SetPos(const VECTOR set) { pos = set; }// �ʒu�Z�b�g

	VECTOR pos;// �ʒu�x�N�g��.
	VECTOR prePos;// �\���ʒu�x�N�g��.
	VECTOR dir;// �����x�N�g��.
	VECTOR targetPos;// �����_�x�N�g��.
};

