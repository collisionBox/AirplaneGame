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
	UI(pos, matRot);
}

void HUDCamera::UI(VECTOR pos, MATRIX matRot)
{
	Lectil(pos, matRot);
	VirticalGyro(pos, matRot);
}

void HUDCamera::VirticalGyro(VECTOR pos, MATRIX matRot)
{
	const float length = 200;
	float posY = WindowY / 2 + 200;
	float angle = VDot(VGet(0.0f, 1.0f, 0.0f), ToYAxis(matRot)) / (VSize(VGet(0.0f, 1.0f, 0.0f) * VSize(ToYAxis(matRot))));
	DrawLineAA(WindowX / 2 - length, posY, WindowX / 2 + length, posY, Green);

}

void HUDCamera::Lectil(VECTOR pos, MATRIX matRot)
{
	const int CenterX = WindowX / 2;
	const int CenterY = WindowY / 2;
	const float Space = 15.0f;
	const float length = 20.0f;
	DrawLineAA(CenterX, CenterY - Space - length, CenterX, CenterY - Space, Green);// 12Žž.
	DrawLineAA(CenterX, CenterY + Space, CenterX, CenterY + Space + length, Green);// 6Žž.
	DrawLineAA(CenterX - Space - length, CenterY, CenterX - Space, CenterY, Green);// 9Žž.
	DrawLineAA(CenterX + Space, CenterY, CenterX + Space + length, CenterY, Green);// 3Žž.
}

void HUDCamera::DebagDraw()
{					
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f:%f:%f", targetPos.x, targetPos.y, targetPos.z);
}

