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
	bullet = new Bullet(ObjectTag::Player);
		
}

Player::~Player()
{
	delete camera;
	delete bullet;
}

void Player::Init()
{

	mat = mat = matScale;

	yaw = pitch = roll = 0.0f;
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;
	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);

	pos = InitPos;
	velocity = InitVec;
	mat = MMult(mat, matRot);

	speed = NomalSpeed;
	velocity = VNorm(ToZAxis(matRot)) * -speed;

	camera->Init(pos, matRot);
	bullet->Init(pos, ToZAxis(matRot));

}

void Player::Update(float deltaTime)
{
	// �X�P�[��.
	mat = matScale;// �@.

	// ��].
	Rotate(deltaTime);

	// �ړ�.
	Movement(deltaTime);

	// ���f.
	MV1SetMatrix(modelHandle, mat);

	// �J����.
	camera->Update(pos, matRot, deltaTime);

	if (CheckHitKey(KEY_INPUT_SPACE))
	{

	}
}

void Player::Rotate(float deltaTime)
{
	// ���[.
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

	// �s�b�`.
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

	// ���[��.
	bool rollFlag = false;
	if (CheckHitKey(KEY_INPUT_A))
	{
		roll = -RollSpeed;
		rollFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		roll = RollSpeed;
		rollFlag = true;
	}
	if (!rollFlag)
	{
		roll = 0.0f;
	}
	roll *= deltaTime;

	// ��]������.
	yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(yaw, yAxis);
	xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(pitch, xAxis);
	zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(roll, zAxis);
	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);// �A.

}

void Player::Movement(float deltaTime)
{
	// ����.
	if (CheckHitKey(KEY_INPUT_LSHIFT) && speed <= MaxSpeed)
	{
		speed += Acceleration;
	}
	// ����.
	else if (CheckHitKey(KEY_INPUT_LCONTROL) && speed >= StallSpeed)
	{
		speed -= Deceleration;
	}
	// �ʏ푬�x�֖߂�.
	else if (!CheckHitKey(KEY_INPUT_LSHIFT) && !CheckHitKey(KEY_INPUT_LCONTROL))
	{
		if (speed <= NomalSpeed)
		{
			speed += Acceleration;
			if (speed > NomalSpeed)
			{
				speed = NomalSpeed;
			}
		}
		else if (speed >= NomalSpeed)
		{
			speed -= Deceleration;
			if (speed < NomalSpeed)
			{
				speed = NomalSpeed;
			}
		}
	}
	// ���f.
	velocity = VNorm(ToZAxis(matRot)) * -speed;
	prePos += velocity * deltaTime;
	pos = prePos;
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matTrans);// �B.
}


void Player::Draw()
{
	int white = GetColor(255, 255, 255);
	MV1DrawModel(modelHandle);
	DrawFormatString(0, 0, white, "%f:%f", VSize(velocity), speed);
	DrawFormatString(0, 20, white, "dir:%f,%f,%f", dir.x, dir.y, dir.z);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

