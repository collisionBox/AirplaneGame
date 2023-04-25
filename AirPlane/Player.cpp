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
	// ヨー.
	bool yawFlag = false;
	if (CheckHitKey(KEY_INPUT_E))
	{
		yaw = YawSpeed;
		yawFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		yaw = -YawSpeed;
		yawFlag = true;
	}
	if (!yawFlag)
	{
		yaw = 0.0f;
	}
	yaw *= deltaTime;

	// ピッチ.
	bool pitchFlag = false;
	if (CheckHitKey(KEY_INPUT_W))
	{
		pitch = -PitchSpeed;
		pitchFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		pitch = PitchSpeed;
		pitchFlag = true;
	}
	if (!pitchFlag)
	{
		pitch = 0.0f;
	}
	pitch *= deltaTime;

	// ロール.
	bool rollFlag = false;
	if (CheckHitKey(KEY_INPUT_A))
	{
		roll = RollSpeed;
		rollFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		roll = -RollSpeed;
		rollFlag = true;
	}
	if (!rollFlag)
	{
		roll = 0.0f;
	}
	roll *= deltaTime;

	mat = MGetScale(VGet(ModelScale, ModelScale, ModelScale));// スケール.
	
	// 回転させる.
	yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(yaw, yAxis);
	xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(pitch, xAxis);
	zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(roll, zAxis);
	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);

	matTrans = MGetTranslate(VGet(0.0f, 0.0f, 0.0f));
	mat = MMult(mat, matTrans);
	MV1SetMatrix(modelHandle, mat);

	if (CheckHitKey(KEY_INPUT_LSHIFT) && VSize(velocity) <= MaxSpeed)
	{
	}
	
	if (CheckHitKey(KEY_INPUT_LCONTROL) && VSize(velocity) >= -MaxSpeed)
	{
	}

	prePos = VAdd(pos, VScale(velocity, deltaTime));
	pos = prePos;
	dir = VNorm(dir);
	//MV1SetPosition(modelHandle, pos);
}

void Player::Draw()
{
	int white = GetColor(255, 255, 255);
	MV1DrawModel(modelHandle);
	DrawFormatString(0, 0, white, "%f%f,%f,%f", quat.t, quat.x, quat.y, quat.z);
	DrawFormatString(0, 20, white, "dir:%f,%f,%f", dir.x, dir.y, dir.z);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

