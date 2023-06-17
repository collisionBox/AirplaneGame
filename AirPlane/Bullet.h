#pragma once
#include "ObjectBase.h"

class Bullet :
    public ObjectBase
{
public:

    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();// ������.
    void Update(float deltaTime)override;
    void Generate(int ModelHandle, int frameIndex, MATRIX matDir);// ��������.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdate��false�ɂ���.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    float CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir);// �p�x���Z�o.
    void Delete();// ��������.
    ObjectTag myTag;
    VECTOR velocity;
    MATRIX mat;
    MATRIX matRot;
    MATRIX matTrans;
    const float modelScale = 0.04f;
    const float ColRadius = 0.1f;// �����蔻�蔼�a.
    const float Speed = 1050.0f;// �e��.
    const float DeadTime = 3.0f;
    float timeCount;
    const float DistanceOfCocpitAndPod = 7.473f;
    const float DistanceOfBodyAndPod = 32.49f;
    //const VECTOR PosCorrection =  AssetManager::GetFramePos()// �e���ʒu�␳.
    const float ZeroInAngle = atanf((GunTargetingDistance + DistanceOfCocpitAndPod)/ DistanceOfBodyAndPod);
};

