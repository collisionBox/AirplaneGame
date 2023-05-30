#include "HUDCamera.h"
#include "Math.h"
#include "AssetManager.h"

void HUDCamera::Init(VECTOR pos, MATRIX matRot, int modelHandle, int frameIndex)
{
	this->pos = AssetManager::GetFramePos(ModelHandle, FrameIndex);
	targetPos = ToZAxis(matRot) * -OffsetLen;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, VNorm(ToYAxis(matRot)));
	ModelHandle = modelHandle;
	FrameIndex = frameIndex;
}

void HUDCamera::Update(VECTOR pos, MATRIX matRot, float deltaTime)
{
	this->pos = AssetManager::GetFramePos(ModelHandle, FrameIndex);
	targetPos = this->pos + ToZAxis(matRot) * -OffsetLen;

	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, ToYAxis(matRot));
	
}

void HUDCamera::DebagDraw()
{
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f:%f:%f", targetPos.x, targetPos.y, targetPos.z);
}

