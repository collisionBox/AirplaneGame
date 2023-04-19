#include "Player.h"
#include "AssetManager.h"
#include "Math.h"
#include <algorithm>
#include <cmath>

using namespace std;

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
	dir = InitVecDir;
	velocity = InitDir;
	upVec = 10.0f;
	power = 0.0f;
	rotateSpeed = 0.0f;
	acceleration = InitVec;
	orientation = InitVec;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Update(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		power += upVec * deltaTime;
		velocity.y += power;
	}
	else
	{
		power -= deltaTime;
		
	}
	if (velocity.y >= MaxUpVec)
	{
		velocity.y = upVec;
	}

	prePos = VAdd(pos, VScale(velocity, deltaTime));
	pos = prePos;
	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

