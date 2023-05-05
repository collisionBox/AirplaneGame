#pragma once
#include "ObjectBase.h"
class Player :
    public ObjectBase
{public:
    Player();
    ~Player();
    void Init();
    void Update(float deltaTime)override;
    void Draw()override;
    void OnCollisionEnter(const ObjectBase* other);
private:

    VECTOR velocity; // ë¨ìx[m/s].
    VECTOR dirAdd;
    VECTOR zAxsisDir;
    const float UpwardAccel = 8.0f;
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const float MaxUpVec = 100.0f;
    const float MaxPower = 100.0f;
    const float Gravity = 9.80665f;
    const VECTOR InitDir = VGet(0.0f, 0.0f, -1.0f);
    const float MaxSpeed = 40.0f;
    const float DefaultDownwardSpeed = -10.0f;// é©ëRç~â∫ë¨ìx.
    VECTOR rotate;

    MATRIX mat;
    MATRIX matRot;
    MATRIX matTrans;
    float yaw, pitch, roll;
    VECTOR xAxis, yAxis, zAxis;
    QUATERNION quat;
    const float ModelScale = 0.015f;
    const float YawSpeed     = 10.0f;
    const float PitchSpeed   = 10.0f;
    const float RollSpeed    = 10.0f;
    MATRIX matVelocity;
};
//http://noa1105.seesaa.net/article/239449116.html
//http://www.f.waseda.jp/moriya/PUBLIC_HTML/education/classes/infomath6/applet/fractal/coord/
//http://marupeke296.com/DXG_No39_WorldMatrixInformation.html
//https://zenn.dev/mebiusbox/books/132b654aa02124/viewer/2966c7