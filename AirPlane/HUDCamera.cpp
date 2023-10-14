#include "HUDCamera.h"
#include "Math.h"
#include "AssetManager.h"

void HUDCamera::Init(VECTOR pos, MATRIX matRot, int modelHandle, int frameIndex)
{
	this->pos = AssetManager::GetFramePos(modelHandle, FrameIndex);
	targetPos = ToZAxis(matRot) * -OffsetLen;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, VNorm(ToYAxis(matRot)));
	ModelHandle = modelHandle;
	FrameIndex = frameIndex;
}

void HUDCamera::Update(VECTOR pos, MATRIX matRot, float deltaTime)
{
	this->pos = GetTransMat2Vec(MV1GetFrameLocalWorldMatrix(ModelHandle, FrameIndex));
	this->pos += ToYAxis(matRot) * AjustY;
	targetPos = this->pos + ToZAxis(matRot) * - GunTargetingDistance;
	SetCameraPositionAndTargetAndUpVec(this->pos, targetPos, ToYAxis(matRot));
}

void HUDCamera::Draw(VECTOR pos, MATRIX matRot, VECTOR velocity)
{
	UI(pos, matRot, velocity);
}

void HUDCamera::UI(VECTOR pos, MATRIX matRot, VECTOR velocity)
{
	Lectil(pos, matRot);
	VirticalGyro(pos, matRot);
	Altimeter(pos.y);
	ElevationMeter(velocity);
	SpeedMeter(velocity);
}

void HUDCamera::VirticalGyro(VECTOR pos, MATRIX matRot)
{
	const float length = 100;
	VECTOR YAxis = ToYAxis(matRot);
	YAxis = YAxis - ToZAxis(matRot) * YAxis.z;
	float angle = FormedAngle(YAxis, VGet(0.0f, 1.0f, 0.0f));
	VECTOR xAxis = ToXAxis(matRot);
	YAxis.y = ((YAxis.y < 0) ? 1 : -1);

	DrawLineAA(CenterX, CenterY, CenterX - length * cosf(angle), CenterY - length * sinf(angle), Green);
	DrawLineAA(CenterX, CenterY, CenterX + length * cosf(angle), CenterY + length * sinf(angle), Green);
	valiavle = ToDegree(angle) * YAxis.y;
}

void HUDCamera::Lectil(VECTOR pos, MATRIX matRot)
{
#if 0
	const float Space = 15.0f;
	const float length = 20.0f;
	DrawLineAA(CenterX, CenterY - Space - length, CenterX, CenterY - Space, Green);// 12Žž.
	DrawLineAA(CenterX, CenterY + Space, CenterX, CenterY + Space + length, Green);// 6Žž.
	DrawLineAA(CenterX - Space - length, CenterY, CenterX - Space, CenterY, Green);// 9Žž.
	DrawLineAA(CenterX + Space, CenterY, CenterX + Space + length, CenterY, Green);// 3Žž.
#else
	const int Orange = GetColor(252, 150, 92);
	DrawCircleAA(CenterX, CenterY, 1, 50, Green, true);// “à‰~.
	DrawCircleAA(CenterX, CenterY, 25, 50, Orange, false, 2.5f);// ŠO‰~.
#endif
}

void HUDCamera::Altimeter(float posY)
{
	const float Space = 6.5f;
	DrawFormatStringF(CenterX + Space * WindowMagnification, CenterY, Green, "%d", (int)posY);
}

void HUDCamera::ElevationMeter(VECTOR velocity)
{
	const float Space = 6.5f;
	const float SpaceY = 20.0f;
	DrawFormatStringF(CenterX + Space * WindowMagnification, CenterY + SpaceY, Green, "%d", (int)velocity.y);
}

void HUDCamera::SpeedMeter(VECTOR velocity)
{
	const float Space = 6.5f;
	DrawFormatStringF(CenterX - Space * WindowMagnification, CenterY, Green, "%d", (int)VSize(velocity));
}

void HUDCamera::DebagDraw()
{					
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f:%f:%f",valiavle);

}

