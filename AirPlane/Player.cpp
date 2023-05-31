#include "Player.h"
#include "AssetManager.h"
#include "ObjectManager.h"
//#include "HUDCamera.h"
//#include "TPCamera.h"
#include "Math.h"
#include <algorithm>
#include <cmath>
using namespace std;

Player::Player() :
	ObjectBase(ObjectTag::Player)
{
	modelHandle = AssetManager::GetMesh("data/player/AH-64 Apache.pmx");
	camera = new CameraManager;
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
	mat = matScale;

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

	camera->Init(pos, matRot, modelHandle, CockpitRearSeat);
	bullet->Init();

	//visible = false;

}

void Player::Update(float deltaTime)
{
	// スケール.
	mat = MGetIdent();// �@.

	// 回転.
	Rotate(deltaTime);

	// 移動.
	Movement(deltaTime);

	// 反映.
	MV1SetMatrix(modelHandle, mat);
	
	RotorRotate(deltaTime);

	// 射撃.
	BulletFire(deltaTime);

	// カメラ.
	camera->Update(pos, matRot);
	//GetTransMat(MV1GetFrameLocalWorldMatrix(modelHandle, CockpitFrontSeat))
	

}

void Player::Rotate(float deltaTime)
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
	姿勢制御平行にするまで姿勢を変える
	if (CheckHitKey(KEY_INPUT_P))
	{
		quat.x = quat.y = quat.z = 0.0f;
		quat.t = 1.0f;

	}

	// 回転させる.
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
	// 加速.
#if 1
	speed = 0;
	if (CheckHitKey(KEY_INPUT_LSHIFT) && speed <= MaxSpeed)
	{
		
		speed = 30;
	}
#else
	if (CheckHitKey(KEY_INPUT_LSHIFT) && speed <= MaxSpeed)
	{
		speed += Acceleration - G;
		
	}
	// 減速.
	else if (CheckHitKey(KEY_INPUT_LCONTROL) && speed >= StallSpeed)
	{
		speed -= Deceleration - G;
	}
	// 通常速度へ戻す.
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
	// 反映.
	velocity = VNorm(ToYAxis(matRot)) * speed;
	prePos += velocity * deltaTime;
	pos = prePos;
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
	MATRIX matMainRotor = AssetManager::MV1GetFrameRotateMatrix(modelHandle, MainRotorFrame, ModelScale, VGet(0.0f, rotateNum, 0.0f));
	MATRIX matTailRotor = AssetManager::MV1GetFrameRotateMatrix(modelHandle, TailRotorFrame, ModelScale, VGet(rotateNum, 0.0f, 0.0f));
	MV1SetFrameUserLocalMatrix(modelHandle, MainRotorFrame, matMainRotor);
	MV1SetFrameUserLocalMatrix(modelHandle, TailRotorFrame, matTailRotor);
	rotateNum++;
	if (rotateNum > 360.0f)
	{
		rotateNum = 0.0f;
	}
	
}



void Player::Draw()
{
	int white = GetColor(255, 255, 255);
	MV1DrawModel(modelHandle);
	VECTOR a = MV1GetFramePosition(modelHandle, MainRotorFrame);
	DrawFormatString(0, 0, white, "%f:%f:%f", pos.x, pos.y, pos.z);
	DrawFormatString(0, 20, white, "%f:%f:%f", a.x, a.y, a.z);
	camera->DebagDraw();
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

