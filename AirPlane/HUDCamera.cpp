#include "HUDCamera.h"
#include "Math.h"
#include "AssetManager.h"
#include "Config.h"

void HUDCamera::Init(VECTOR pos, MATRIX matRot, int modelHandle, int frameIndex)
{
	this->pos = AssetManager::GetFramePos(modelHandle, FrameIndex);
	targetPos = ToZAxis(matRot) * -OffsetLen;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, VNorm(ToYAxis(matRot)));
	ModelHandle = modelHandle;
	FrameIndex = frameIndex;
}

void HUDCamera::Update(VECTOR pos, MATRIX matRot)
{
	this->pos = GetTransMat2Vec(MV1GetFrameLocalWorldMatrix(ModelHandle, FrameIndex));
	this->pos += ToYAxis(matRot) * AjustY;
	targetPos = this->pos + ToZAxis(matRot) * -OffsetLen;

	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, ToYAxis(matRot));
}

void HUDCamera::Draw(VECTOR pos, MATRIX matRot)
{
}

void HUDCamera::UI(VECTOR pos, MATRIX matRot)
{
	SwivelMeter(pos, matRot);
}

void HUDCamera::SwivelMeter(VECTOR pos, MATRIX matRot)
{
	float angle = VDot(VGet(0.0f, 1.0f, 0.0f), ToYAxis(matRot)) / (VSize(VGet(0.0f, 1.0f, 0.0f) * VSize(ToYAxis(matRot))));
	DrawLine3D
}

void HUDCamera::DebagDraw()
{					
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f:%f:%f", targetPos.x, targetPos.y, targetPos.z);
}

