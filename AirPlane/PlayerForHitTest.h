#pragma once
#include "ObjectBase.h"

// 当たり判定用プレイヤーオブジェクト
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

