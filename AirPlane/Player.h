#pragma once
#include "ObjectBase.h"
#include "HUDCamera.h"
#include "BulletManager.h"
#include <memory>
class Player :
    public ObjectBase
{
public:
    Player();
    ~Player();
    void Init();
    void Update(float deltaTime)override;
    void Draw()override;
    void OnCollisionEnter(const ObjectBase* other);
private:
    void Rotate(float deltaTime);
    void Movement(float deltaTime);
    void BulletFire(float deltaTime);

    HUDCamera* camera;
    BulletManager* bullet;
    const int MaxBulletsNum = 20;


    VECTOR velocity; // 速度[m/s].
    const float Acceleration = 36.0f;// 加速度.
    const float MaxSpeed = 2575.0f;// 最高速度.
    const float Deceleration = 20.0f;// 減速度.
    const float StallSpeed = 220.0f;// 失速速度.
    const float NomalSpeed = 600.0f;// 通常速度.
    float speed;
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const VECTOR InitPos = VGet(0.0f, 100.0f, 0.0f);// 初期位置.
    MATRIX mat;// ワールド座標.
    MATRIX matRot;// 回転行列.
    MATRIX matTrans;// 移動行列.
    MATRIX matLocal;// ローカル座標.
    float yaw, pitch, roll;
    VECTOR xAxis, yAxis, zAxis;
    QUATERNION quat;
    const float ModelScale = 0.015f;
    const float YawSpeed     = 1.05f;
    const float PitchSpeed   = 1.6f;
    const float RollSpeed    = 1.8f;
    const MATRIX matScale = MGetScale(VGet(ModelScale, ModelScale, ModelScale));// スケール行列.

};
//http://noa1105.seesaa.net/article/239449116.html
//http://www.f.waseda.jp/moriya/PUBLIC_HTML/education/classes/infomath6/applet/fractal/coord/
//http://marupeke296.com/DXG_No39_WorldMatrixInformation.html
//https://zenn.dev/mebiusbox/books/132b654aa02124/viewer/2966c7
//https://yttm-work.jp/gmpg/gmpg_0002.html