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
    void Generate(VECTOR pos, MATRIX matDir);// ¶¬ˆ—.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdate‚ğfalse‚É‚·‚é.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    float CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir);// Šp“x‚ğZo.
    void Delete();// Á‚·ˆ—.
    ObjectTag myTag;
    VECTOR velocity;
    const float modelScale = 0.004f;
    const float ColRadius = 0.1f;// “–‚½‚è”»’è”¼Œa.
    const float Speed = 1050.0f;// ’e‘¬.
    const float DeadTime = 3.0f;
    float timeCount;
    const VECTOR PosCorrectionScale = VGet(-1.2f, 0.0f, -5.0f);// eŒûˆÊ’u•â³’è”.
    const float GunTargetingDistance = 800.0f;
};

