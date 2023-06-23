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
	void Update(VECTOR pos, MATRIX matRot, float deltaTime);
	void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity);
	void DebagDraw();
	const bool IsModelDraw() { return modelVisible; }

private:
	bool inputFlag;
	bool modelVisible;
	int cameraNum;
	unordered_map<int, CameraBase*>camera;
};

