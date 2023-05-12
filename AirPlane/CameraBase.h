#pragma once
#include "DxLib.h"
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Update(VECTOR pos, MATRIX matRot, float deltaTime) = 0;  // ゲームオブジェクト更新処理

protected:
	void SetPos(const VECTOR set) { pos = set; }// 位置セット

	VECTOR pos;// 位置ベクトル.
	VECTOR targetPos;// 注視点ベクトル.
};

