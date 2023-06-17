#pragma once
#include "ObjectBase.h"

class Bullet :
    public ObjectBase
{
public:

    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();// ‰Šú‰».
    void Update(float deltaTime)override;
    void Generate(int ModelHandle, int frameIndex, MATRIX matDir);// ¶¬ˆ—.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdate‚ğfalse‚É‚·‚é.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    float CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir);// Šp“x‚ğZo.
    void Delete();// Á‚·ˆ—.
    ObjectTag myTag;
    VECTOR velocity;
    MATRIX mat;
    MATRIX matRot;
    MATRIX matTrans;
    const float modelScale = 0.04f;
    const float ColRadius = 0.1f;// “–‚½‚è”»’è”¼Œa.
    const float Speed = 1050.0f;// ’e‘¬.
    const float DeadTime = 3.0f;
    float timeCount;
    const float DistanceOfCocpitAndPod = 7.473f;
    const float DistanceOfBodyAndPod = 32.49f;
    //const VECTOR PosCorrection =  AssetManager::GetFramePos()// eŒûˆÊ’u•â³.
    const float ZeroInAngle = atanf((GunTargetingDistance + DistanceOfCocpitAndPod)/ DistanceOfBodyAndPod);
};

