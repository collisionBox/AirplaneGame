#pragma once
#include "DxLib.h"
class CameraBase
{
public:
	virtual void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex) = 0;// 初期化.
	virtual void Update(VECTOR pos, MATRIX matRot) = 0;  // 更新処理
	virtual void DebagDraw() {};

protected:
	void SetPos(const VECTOR set) { pos = set; }// 位置セット

	VECTOR pos;// 位置ベクトル.
	VECTOR targetPos;// 注視点ベクトル.
};

