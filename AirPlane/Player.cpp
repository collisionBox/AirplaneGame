#include "Player.h"
#include "AssetManager.h"
Player::Player() :
	ObjectBase(ObjectTag::Player)
{
	modelHandle = AssetManager::GetMesh("data/player/player.mv1");
	MV1SetScale(modelHandle, VGet(0.05f, 0.05f, 0.05f));
	
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	pos = InitVec;
	dir = VScale(InitVecDir, -1);
	velocity = InitVec;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Update(float deltaTime)
{
	float v = VSize(velocity);// ‘¬“x.


}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}
https://sites.google.com/view/ronsu900/createfs/wing1
AoA‚©‚çCL‚Ü‚ÅZo‚·‚éŠÖ”‚ğì¬.
//------------------------------------------------------------------------------
// @brief ‹ÂŠp(AngleOfAttack)‚ÌZo.
//------------------------------------------------------------------------------
float Player::CalculataAoA()
{
	return ToRadian(atan2f(velocity.y, velocity.z));
}

//------------------------------------------------------------------------------
// @brief —g—ÍŒW”‚ÌZo.
//------------------------------------------------------------------------------
float Player::CalculateCL()
{
	return CalculataAoA() * 0.1f;
}
