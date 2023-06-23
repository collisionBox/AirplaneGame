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
    void Delete();// Á‚·ˆ—.
    ObjectTag myTag;  
    VECTOR velocity;
    const float modelScale = 0.2f;
    const float ColRadius = 0.5f;// ’e“ª“–‚½‚è”»’è”¼Œa.[m]
    //const float Speed = 44400.0f;// ’e‘¬.[m/h]
    const float MaxSpeed = 740.0f;// ’e‘¬.[m/s]
    const float acceleration = 740.0f;
    float speed;
    const float DeadTime = 3.0f;// íœŠÔ.
    const float BlastTime = 0.8f;// ”š”­”¼Œa—LŒøŠÔ.
    const float AccelerationTime = 1.0f;// ‰Á‘¬ŠÔ.
    float timeCount;
};

