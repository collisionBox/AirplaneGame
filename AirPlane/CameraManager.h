#pragma once
#include "DxLib.h"
#include <unordered_map>
#include "CameraBase.h"
using namespace std;
class CameraManager
{
public:
	CameraManager();
	void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex);
	void Update(VECTOR pos, MATRIX matRot);
	void DebagDraw();

private:
	bool inputFlag;
	int cameraNum;
	unordered_map<int, CameraBase*>camera;
};

