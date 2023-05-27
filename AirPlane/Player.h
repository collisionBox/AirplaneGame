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
    void RotorRotate(float deltaTime);

    HUDCamera* camera;
    BulletManager* bullet;
    const int MaxBulletsNum = 20;
    const float FiringInterval = 0.1f;
    float intervalTime;
    
    VECTOR velocity; // ���x[m/s].
    const float Acceleration = 36.0f;// �����x.
    const float MaxSpeed = 2575.0f;// �ō����x.
    const float Deceleration = 20.0f;// �����x.
    const float StallSpeed = 220.0f;// �������x.
    const float NomalSpeed = 600.0f;// �ʏ푬�x.
    float speed;
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const VECTOR InitPos = VGet(0.0f, 100.0f, 0.0f);// �����ʒu.
    MATRIX mat;// ���[���h���W.
    MATRIX matRot;// ��]�s��.
    MATRIX matTrans;// �ړ��s��.
    MATRIX matLocal;// ���[�J�����W.
    float yaw, pitch, roll;
    QUATERNION quat;
    const float ModelScale = 0.08f;
    const float YawSpeed     = 1.05f;
    const float PitchSpeed   = 1.0f;
    const float RollSpeed    = 1.8f;
    const MATRIX matScale = MGetScale(VGet(ModelScale, ModelScale, ModelScale));// �X�P�[���s��.
    const float G = 9.80665f;// �d�͉����x[m/s2].
    const int MainRotorFrame = 8;// ���C�����[�^�[�t���[���i���o�[.
    const VECTOR MainRotorPos = VGet(0.0f, 36.486f, -46.728f);
    const int TailRotorFrame = 12;// �e�[�����[�^�[�t���[���i���o�[.
    const VECTOR TailRotorPos = VGet(4.231f,40.900f,80.611f) * ModelScale;
    const int ChainGunRotateFrame = 14;// �`�F�[���K����]���t���[���i���o�[.
    const VECTOR ChainGunRotatePos = VGet(0.143f, 10.999f, -84.701f);
    const int ChainGunElevationAngleFlame = 15;// �`�F�[���K���p�t���[���i���o�[.
    const VECTOR ChainGunElevationAnglePos = VGet(0.582f, -6.088f, 0.460f);
    const int ChainGunMuzzleFlame = 16;// �`�F�[���K���e���t���[���i���o�[.
    const VECTOR ChainGunMuzzlePos = VGet(0.726f, 0.627f, -20.396f);
   
    float rotateNum;
    int attachIndex;
    float animTotalPlayTime, animPlayTime;
};
//http://noa1105.seesaa.net/article/239449116.html
//http://www.f.waseda.jp/moriya/PUBLIC_HTML/education/classes/infomath6/applet/fractal/coord/
//http://marupeke296.com/DXG_No39_WorldMatrixInformation.html
//https://zenn.dev/mebiusbox/books/132b654aa02124/viewer/2966c7
//https://yttm-work.jp/gmpg/gmpg_0002.html