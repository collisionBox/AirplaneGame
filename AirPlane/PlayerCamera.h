#pragma once
#include "ObjectBase.h"
class PlayerCamera :
    public ObjectBase
{
public:
    PlayerCamera();
    ~PlayerCamera() {};
    void Init();
    void Update(float deltaTime);
    void Input(float deltaTime);
    void Draw();
private:
    float acceleration;// アクセルに追加する加速度.
    float accel;
    const float InitAccel = 30.0f;
    VECTOR velosity;
    VECTOR aimPos;// 注視点目標.
    VECTOR prePos;// 予測ポジション.
    float roll;
    float rollInclement;
    const float DefaultLength = 50.0f;
    float length;
};

