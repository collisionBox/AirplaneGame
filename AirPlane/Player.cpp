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
	mat = MGetIdent();// ①.

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

	// ロール.
	bool rollFlag = false;
	if (CheckHitKey(KEY_INPUT_A))
	{
		roll += -RollAccelAndDecel;
		rollFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		roll += RollAccelAndDecel;
		rollFlag = true;
	}
	if (roll > MaxRollSpeed || roll < -MaxRollSpeed)
	{
		roll = MaxRollSpeed * ((roll > 0) ? 1.0f : -1.0f);
	}
	if (!rollFlag)
	{
	http://www7.plala.or.jp/kfb/program/stg2dvec.html
		if (!IsNearAngle(VGet(0,1,0), ToYAxis(mat)))
		{
			
		}
		//roll = 0.0f;

	}
	valiable = deltaTime;
	// クォータニオンから回転行列に変換.
	VECTOR yAxis = ToYAxis(mat);// yaw.
	quat = quat * CreateRotationQuaternion(ToRadian(yaw) * deltaTime, yAxis);
	VECTOR xAxis = ToXAxis(mat);// pitch.
	quat = quat * CreateRotationQuaternion(ToRadian(pitch) * deltaTime, xAxis);
	VECTOR zAxis = ToZAxis(mat);// roll.
	quat = quat * CreateRotationQuaternion(ToRadian(roll) * deltaTime, zAxis);
	MATRIX matRotVel = QuaternionToMatrix(quat);
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;

	if (prePos.y <= 0.0f)
	{
	//	matRotVel = ( MInverse(MGetRotVec2(VGet(0.0f, 1.0f, 0.0f), ToYAxis(matRot))));

	}

	if (CheckHitKey(KEY_INPUT_P)) 
	{

	}
	matRot = MMult(matRot, matRotVel);
	mat = MMult(mat, matRot);// ②.
}

void Player::Movement(float deltaTime)
{
	// 加速.
#if 1
	power = 0;
	if (CheckHitKey(KEY_INPUT_LSHIFT) && power <= 100)
	{
		power = 50;
	}
	else
	{
		if (pos.y > 0)
		{
			gVelo -= G * deltaTime;
		}
	}
	if (CheckHitKey(KEY_INPUT_LCONTROL) && power >= 0)
	{
		power -= 10;
	}
	
	if (pos.y <= 0)
	{
		pos.y = 0;
	}
#else
	if (CheckHitKey(KEY_INPUT_LSHIFT) && speed <= MaxSpeed)
	{
		speed += Acceleration - G;
		
	}
	// 減速.
	
#endif	

	// 反映.
	velocity = VNorm(ToYAxis(matRot)) * power;
	velocity.y += gVelo;
	prePos += velocity * deltaTime;
	if (prePos.y <= 0)
	{
		prePos.y = 0;
	}
	if (pos.y <= 0)
	{
		gVelo = 0;
	}
	pos = prePos;
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matTrans);// ③.
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
	DrawFormatString(0, 0, white, "%f:%f:%f", pos.x, pos.y, pos.z);
	DrawFormatString(0, 20, white, "%f:%f:%f", ToYAxis(mat).y, roll);
	camera->DebagDraw();
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

