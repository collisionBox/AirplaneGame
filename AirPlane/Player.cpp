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
	camera = new HUDCamera();
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	camera->Init();
	pos = VGet(0,5,0);
	dir = InitDir;
	dirAdd = InitVec;
	velocity = InitVec;
	rotate = InitVec;

	yaw = pitch = roll = 0.0f;
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;
	matRot = QuaternionToMatrix(quat);
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationXYZ(modelHandle, dir);
}

void Player::Update(float deltaTime)
{
	// ÉXÉPÅ[Éã.
	mat = matScale;// á@.

	// âÒì].
	// ÉàÅ[.
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

	// ÉsÉbÉ`.
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

	// ÉçÅ[Éã.
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


	// âÒì]Ç≥ÇπÇÈ.
	yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(yaw, yAxis);
	xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(pitch, xAxis);
	zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(roll, zAxis);
	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);// áA.

	// à⁄ìÆ.
	VECTOR dirX = ToXAxis(matRot);
	VECTOR dirY = ToYAxis(matRot);
	VECTOR dirZ = ToZAxis(matRot);

	if (CheckHitKey(KEY_INPUT_LSHIFT) && VSize(velocity) <= MaxSpeed)
	{
		velocity = VNorm(dirZ) * -UpwardAccel;
	}
	
	if (CheckHitKey(KEY_INPUT_LCONTROL) && VSize(velocity) >= -MaxSpeed)
	{
	}
	prePos = VAdd(pos, VScale(velocity, deltaTime));
	pos = prePos;
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matTrans);// áB.
	
	// îΩâf.
	MV1SetMatrix(modelHandle, mat);

	// ÉJÉÅÉâ.
	camera->Update(pos, matRot, deltaTime);
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

