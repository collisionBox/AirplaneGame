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
	mat = MGetScale(VGet(ModelScale, ModelScale, ModelScale));

	Init();
}

Player::~Player()
{
}

void Player::Init()
{


	pos = InitVec;
	dir = InitDir;
	dirAdd = InitVec;
	zAxsisDir = VGet(0, 1, 0);// ロールの制御ができそう？
	velocity = InitVec;
	rotate = InitVec;

	yaw = pitch = roll = 0.0f;
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;




	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Update(float deltaTime)
{
	VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
	VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
	bool yawFlag = false;
	// ヨー.
	if (CheckHitKey(KEY_INPUT_E))
	{
		yaw += 0.1f;
		yawFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		yaw -= 0.1f;
		yawFlag = true;
	}
	if (!yawFlag)
	{
		yaw = 0.0f;
	}
	// ピッチ.
	bool pitchFlag = false;
	if (CheckHitKey(KEY_INPUT_W))
	{
		pitch += 0.1f;
		pitchFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		pitch -= 0.1f;
		pitchFlag = true;
	}
	if (!pitchFlag)
	{
		pitch = 0.0f;
	}
	// ロール.
	bool rollFlag = false;
	if (CheckHitKey(KEY_INPUT_A))
	{
		roll += 0.1f;
		rollFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		roll -= 0.1f;
		rollFlag = true;
	}
	if (!rollFlag)
	{
		roll = false;
	}

	zAxis = ToZAxis(mat);
	quat = quat * CreateRotationQuaternion(roll, zAxis);

	xAxis = ToXAxis(mat);
	quat = quat * CreateRotationQuaternion(pitch, xAxis);

	yAxis = ToXAxis(mat);
	quat = quat * CreateRotationQuaternion(yaw, yAxis);

	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);
	MGetAxis1(xAxis, yAxis, zAxis, pos);
	//MV1SetMatrix(modelHandle, mat);

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
	dir = VNorm(dir);
	MV1SetPosition(modelHandle, pos);
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

