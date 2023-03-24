#include "PlayerForHitTest.h"
PlayerForHitTest::PlayerForHitTest()
{
	
	Init();
}

PlayerForHitTest::~PlayerForHitTest()
{
}

void PlayerForHitTest::Init()
{
	pos = InitVec;
}

void PlayerForHitTest::Update(float deltaTime)
{
}

void PlayerForHitTest::Draw()
{

}
void PlayerForHitTest::OnCollisionEnter(const ObjectBase* other)
{
}
