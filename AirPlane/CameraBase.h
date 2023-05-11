#pragma once
#include "DxLib.h"
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Init() = 0;
	virtual void Update(VECTOR pos, MATRIX matRot, float deltaTime) = 0;  // ゲームオブジェクト更新処理

protected:
	void SetPos(const VECTOR set) { pos = set; }// 位置セット

	VECTOR pos;// 位置ベクトル.
	VECTOR prePos;// 予測位置ベクトル.
	VECTOR dir;// 方向ベクトル.
	VECTOR targetPos;// 注視点ベクトル.
};

