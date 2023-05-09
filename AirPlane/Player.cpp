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

	pos = VGet(0,5,0);
	dir = InitDir;
	dirAdd = InitVec;
	velocity = InitVec;
	rotate = InitVec;

	yaw = pitch = roll = 0.0f;
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;
	matRot = QuaternionToMatrix(quat);
	matVelocity = InitMat;
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationXYZ(modelHandle, dir);

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

	
	// 回転させる.
	yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(yaw, yAxis);
	xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(pitch, xAxis);
	zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(roll, zAxis);
	matRot = QuaternionToMatrix(quat);
	MATRIX matDir = { mat.m[0][0],mat.m[0][1],mat.m[0][2],
					  mat.m[1][0],mat.m[1][1],mat.m[1][2],
					  mat.m[2][0],mat.m[2][1],mat.m[2][2] };
	VECTOR dirX = VScale(VGet(mat.m[0][0], mat.m[0][1], mat.m[0][2]), ModelScale);
	VECTOR dirY = VScale(VGet(mat.m[1][0], mat.m[1][1], mat.m[1][2]), ModelScale);
	VECTOR dirZ = VScale(VGet(mat.m[2][0], mat.m[2][1], mat.m[2][2]), ModelScale);

	dir = VGet(VSize(dirX), VSize(dirY), VSize(dirZ));
	pos = InitVec;
	if (CheckHitKey(KEY_INPUT_LSHIFT) && VSize(velocity) <= MaxSpeed)
	{
		pos = VGet(5, 5, 5);
		
	}
	
	if (CheckHitKey(KEY_INPUT_LCONTROL) && VSize(velocity) >= -MaxSpeed)
	{
	}
	//MV1SetRotationXYZ(modelHandle, dir);
	/*prePos = VAdd(pos, VScale(velocity, deltaTime));
	pos = prePos;*/
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matScale);
	mat = MMult(mat, matRot);
	mat = MMult(mat, matTrans);

	mat = MTranspose(mat);
	MV1SetMatrix(modelHandle, mat);
//https://qiita.com/kenjihiranabe/items/945232fbde58fab45681
}

void Player::Draw()
{
	int white = GetColor(255, 255, 255);
	MV1DrawModel(modelHandle);
	DrawFormatString(0, 0, white, "%f%f,%f,%f", quat.t, quat.x, quat.y, quat.z);
	DrawFormatString(0, 20, white, "dir:%f,%f,%f", dir.x, dir.y, dir.z);
	DrawFormatString(0, 40, white, "  %f %f %f %f\n % f % f % f % f\n % f % f % f % f\n % f % f % f % f",
		mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3], mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
		mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3], mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

