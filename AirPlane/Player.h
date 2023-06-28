#pragma once
#include "ObjectBase.h"
#include "CameraManager.h"
#include "BulletManager.h"
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
    void RotateDecel(float& axis, float deceleration);
    void Movement(float deltaTime);
    void BulletFire(float deltaTime);
    void RotorRotate(float deltaTime);

    CameraManager* camera;
    BulletManager* bullet;
    const int MaxBulletsNum = 20;
    const float FiringInterval = 0.1f;
    float intervalTime;
    
    // 機体関係.
    VECTOR velocity; // 速度[m/s].
    VECTOR worldVel;// ワールド速度.
    const float Acceleration = 36.0f;// 加速度.
    const float MaxSpeed = 295.0f;// 最高速度[m/h].
    const float MaxAltitude = 5400.0f;// 最高高度[m].
    const float UpliftRate = 11.5f;// 垂直上昇率[m].
    const float Weight = 7.0f;//重量[t] 
    //const float Deceleration = 20.0f;// 減速度.
    //const float StallSpeed = 220.0f;// 失速速度.
    //const float NomalSpeed = 600.0f;// 通常速度.
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const VECTOR InitPos = VGet(0.0f, 100.0f, 0.0f);// 初期位置.
    const float ModelScale = 0.08f;// スケール.

    const float YawAccelAndDecel = 3.0f;
    const float MaxYawSpeed = 150.0f;

    const float PitchAccelAndDecel = 2.0f;
    const float MaxPichSpeed = 100.0f;

    const float RollAccelAndDecel = 5.0f;
    const float MaxRollSpeed = 105.0f;

    const MATRIX matScale = MGetScale(VGet(ModelScale, ModelScale, ModelScale));// スケール行列.
    //float speed;
    float power = 0;
    MATRIX mat;// ワールド座標.
    MATRIX matRot;// 回転行列.
    MATRIX matTrans;// 移動行列.
    MATRIX matLocal;// ローカル座標.
    float yaw, pitch, roll;
    QUATERNION quat;// 方向クォータニオン.
    int prevMouseX, prevMouseY;


    // フレーム番号.
    const int MainRotorFrame = 8;// メインローターフレームナンバー.
    const int TailRotorFrame = 12;// テールローターフレームナンバー.
    const int ChainGunRotateFrame = 14;// チェーンガン回転軸フレームナンバー.
    const int ChainGunElevationAngleFlame = 15;// チェーンガン仰角フレームナンバー.
    const int ChainGunMuzzleFlame = 16;// チェーンガン銃口フレームナンバー.
    const int CockpitFrontSeat = 21;// コックピット前席.
    const int CockpitRearSeat = 22;// コックピット後席.
    const int MissilepodR = 23;// 右ミサイルポッド.
    const int MissilepodL = 24;// 左ミサイルポッド.

    float rotateNum;

    // デバッグ系.
    float valiable[2];
    VECTOR qwe;
};
//http://noa1105.seesaa.net/article/239449116.html
//http://www.f.waseda.jp/moriya/PUBLIC_HTML/education/classes/infomath6/applet/fractal/coord/
//http://marupeke296.com/DXG_No39_WorldMatrixInformation.html
//https://zenn.dev/mebiusbox/books/132b654aa02124/viewer/2966c7
//https://yttm-work.jp/gmpg/gmpg_0002.html