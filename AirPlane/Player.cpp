#include "Player.h"
#include "AssetManager.h"
#include "ObjectManager.h"
#include "Math.h"
#include <algorithm>
#include <cmath>
using namespace std;

Player::Player() :
	ObjectBase(ObjectTag::Player)
{
	modelHandle = AssetManager::GetMesh("data/player/AH-64 Apache.pmx");
	camera = new HUDCamera();
	bullet = new BulletManager(ObjectTag::Player);
	Init();
		
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

	prePos = pos = InitVec;
	mat = MMult(mat, matRot);

	speed = NomalSpeed;
	velocity = VNorm(ToZAxis(matRot)) * -speed;
	rotateNum = 0.0f;

	camera->Init(pos, matRot);
	bullet->Init();

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

	MATRIX matRotMainRotor = AssetManager::MV1GetFrameRotateMatrix(modelHandle, MainRotorFrame, 0, rotateNum, 0, ModelScale);
	//MATRIX matRotMainRotor = AssetManager::GetFrameRotateMatrix(modelHandle, MainRotorFrame, ModelScale, 0, rotateNum, 0,ToXAxis(matRot), ToYAxis(matRot), ToZAxis(matRot));
	MV1SetFrameUserLocalMatrix(modelHandle, MainRotorFrame, matRotMainRotor);
	rotateNum++;

	// �ˌ�.
	BulletFire(deltaTime);

	// �J����.
	camera->Update(pos, matRot, deltaTime);

	

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
	VECTOR yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(yaw, yAxis);
	VECTOR xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(pitch, xAxis);
	VECTOR zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(roll, zAxis);
	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);// �A.

}

void Player::Movement(float deltaTime)
{
	// ����.
#if 1
	speed = 0;
	if (CheckHitKey(KEY_INPUT_LSHIFT) && speed <= MaxSpeed)
	{
		
		speed = 10;
	}
#else
	if (CheckHitKey(KEY_INPUT_LSHIFT) && speed <= MaxSpeed)
	{
		speed += Acceleration - G;
		
	}
	// ����.
	else if (CheckHitKey(KEY_INPUT_LCONTROL) && speed >= StallSpeed)
	{
		speed -= Deceleration - G;
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
#endif	
	// ���f.
	velocity = VNorm(ToYAxis(matRot)) * speed;
	prePos += velocity * deltaTime;
	//pos = prePos;
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matTrans);// �B.
}

void Player::BulletFire(float deltaTime)
{
	intervalTime -= deltaTime;
	if (intervalTime <= 0 && CheckHitKey(KEY_INPUT_SPACE))
	{
		bullet->Generater(prePos, matRot);
		intervalTime = FiringInterval;
	}


	
}

void Player::RotorRotate(float deltaTime)
{
}


void Player::Draw()
{
	int white = GetColor(255, 255, 255);
	MV1DrawModel(modelHandle);
	DrawFormatString(0, 0, white, "%f:%f:%f", pos.x, pos.y, pos.z);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

