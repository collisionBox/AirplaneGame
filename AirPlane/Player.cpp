#include "Player.h"
#include "AssetManager.h"
Player::Player() :
	ObjectBase(ObjectTag::Player)
{
	modelHandle = AssetManager::GetMesh("data/player/player.mv1");
	MV1SetScale(modelHandle, VGet(0.05f, 0.05f, 0.05f));
	pos = InitVecPos;
	dir = VScale(InitVecDir, -1);
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}
