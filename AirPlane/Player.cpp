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
	dirAdd = InitVec;
	velocity = InitVec;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Update(float deltaTime)
{
	VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
	VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
	if (CheckHitKey(KEY_INPUT_E))// ヨー（右）.
	{
		dirAdd = VAdd(dir, VScale(right, YowSpeed));
	}
	if (CheckHitKey(KEY_INPUT_Q))// ヨー（左）.
	{
		
		dirAdd = VAdd(dir, VScale(left, YowSpeed));
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		VECTOR cross = VCross(dir, left);
		dirAdd = VAdd(dir, VScale(cross, YowSpeed));
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
	}

	if (CheckHitKey(KEY_INPUT_A))
	{

	}
	if (CheckHitKey(KEY_INPUT_D))
	{

	}
	if (CheckHitKey(KEY_INPUT_LSHIFT) && VSize(velocity) <= MaxSpeed)// 上昇.
	{
		VECTOR upward = VCross(left, dir);
		velocity = VAdd(velocity, VScale(upward, UpwardAccel));
	}
	else if (!CheckHitKey(KEY_INPUT_LSHIFT) && velocity.y > DefaultDownwardSpeed)
	{
		velocity.y -= DefaultDownwardAccel;
		if (velocity.y <= DefaultDownwardSpeed)
		{
			velocity.y = DefaultDownwardSpeed;
		}
	}
	
	if (CheckHitKey(KEY_INPUT_LCONTROL) && VSize(velocity) >= -MaxSpeed)// 下降.
	{
		VECTOR downward = VCross(dir, left);
		velocity = VAdd(velocity, VScale(downward, DownwardAccel));
	}
	else if (!CheckHitKey(KEY_INPUT_LCONTROL) && velocity.y < DefaultDownwardSpeed)
	{
		velocity.y += DefaultUpwardAccel;
		if (velocity.y >= DefaultDownwardSpeed)
		{
			velocity.y = DefaultDownwardSpeed;
		}
	}

	prePos = VAdd(pos, VScale(velocity, deltaTime));
	if (prePos.y < 0.0f)
	{
		velocity.y = 0.0f;
		prePos.y = 0.0f;
		dir.y = 0.0f;
	}
	pos = prePos;
	dir = VAdd(dir, VScale(dirAdd, deltaTime));
	dir = VNorm(dir);
	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Draw()
{
	int white = GetColor(255, 255, 255);
	MV1DrawModel(modelHandle);
	DrawFormatString(0, 0, white, "vel:%f", velocity.y);
	DrawFormatString(0, 20, white, "dir:%f,%f,%f", dir.x, dir.y, dir.z);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

