#pragma once
#include "ObjectBase.h"

// �����蔻��p�v���C���[�I�u�W�F�N�g
class PlayerForHitTest :
    public ObjectBase
{
public:

    PlayerForHitTest();
    ~PlayerForHitTest();
    void Init();
    void Update(float deltaTime)override;
    void Draw()override;
    void OnCollisionEnter(const ObjectBase* other)override;

private:

};

