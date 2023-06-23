#pragma once
#include "CameraBase.h"
#include "Config.h"

class HUDCamera :
    public CameraBase
{
public: 
    static HUDCamera GetInstance() { HUDCamera Instance; return Instance; }
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot, float deltaTime)override;
    void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity)override;
    void UI(VECTOR pos, MATRIX matRot, VECTOR velocity);
    const VECTOR GetPos()const { return pos; }
    void DebagDraw()override;
private:
    void VirticalGyro(VECTOR pos, MATRIX matRot);// 姿勢指示器
    void Lectil(VECTOR pos, MATRIX matRot);// 照準.
    void Altimeter(float posY);// 高度計.
    void ElevationMeter(VECTOR velocity);// 昇降計.
    void SpeedMeter(VECTOR velocity);// 速度計.
    static HUDCamera* Instance;

    const float OffsetLen = 10.0f;
    const float OffsetY = 50.0f;
    const float AjustY = 7.85f;// 人間の視界の高さにする.
    int ModelHandle;
    int FrameIndex;
    const float SwivelMeterLineLen = 50.0f;// 姿勢指示器のLINEの長さ.
    const int Green = GetColor(40, 255, 40);
    const float CenterX = (float)WindowX / 2;
    const float CenterY = (float)WindowY / 2;
    float valiavle;
};

