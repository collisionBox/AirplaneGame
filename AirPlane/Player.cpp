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
	attachIndex = MV1AttachAnim(modelHandle, 0, -1, false);
	animTotalPlayTime = MV1GetAnimTotalTime(modelHandle, attachIndex);
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
	animPlayTime = 0.0f;
	MV1SetAttachAnimTime(modelHandle, attachIndex, animPlayTime);

	camera->Init(pos, matRot);
	bullet->Init();

}

void Player::Update(float deltaTime)
{
	// ÉXÉPÅ[Éã.
	mat = MGetIdent();// á@.

	// âÒì].
	Rotate(deltaTime);

	// à⁄ìÆ.
	Movement(deltaTime);

	// îΩâf.
	MV1SetMatrix(modelHandle, mat);
	MV1SetAttachAnimTime(modelHandle, attachIndex, animPlayTime);
	animPlayTime += deltaTime;
	if (animPlayTime >= animTotalPlayTime)
	{
		animPlayTime = 0.0f;
	}
	
	RotorRotate(deltaTime);

	// éÀåÇ.
	BulletFire(deltaTime);

	// ÉJÉÅÉâ.
	camera->Update(pos, matRot,ModelScale, deltaTime);

	

}

void Player::Rotate(float deltaTime)
{
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

	// âÒì]Ç≥ÇπÇÈ.
	VECTOR yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(yaw, yAxis);
	VECTOR xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(pitch, xAxis);
	VECTOR zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(roll, zAxis);
	matRot = QuaternionToMatrix(quat);
	mat = MMult(mat, matRot);// áA.
}

void Player::Movement(float deltaTime)
{
	// â¡ë¨.
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
	// å∏ë¨.
	else if (CheckHitKey(KEY_INPUT_LCONTROL) && speed >= StallSpeed)
	{
		speed -= Deceleration - G;
	}
	// í èÌë¨ìxÇ÷ñﬂÇ∑.
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
	// îΩâf.
	velocity = VNorm(ToYAxis(matRot)) * speed;
	prePos += velocity * deltaTime;
	pos = prePos;
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matTrans);// áB.
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
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

