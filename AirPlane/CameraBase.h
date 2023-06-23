#pragma once
#include "DxLib.h"
#include <cmath>
class CameraBase
{
public:
	virtual void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex) = 0;// 初期化.
	virtual void Update(VECTOR pos, MATRIX matRot, float deltaTime) = 0;  // 更新処理
	virtual void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity) {};
	virtual void DebagDraw() {};// デバッグ用.

protected:
	void SetPos(const VECTOR set) { pos = set; }// 位置セット

	VECTOR pos;// 位置ベクトル.
	VECTOR targetPos;// 注視点ベクトル.
};

