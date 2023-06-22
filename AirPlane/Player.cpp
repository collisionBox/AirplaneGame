#include "Player.h"
#include "AssetManager.h"
#include "ObjectManager.h"
#include "Config.h"
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
	velocity = VNorm(ToZAxis(matRot));
	rotateNum = 0.0f;

	camera->Init(pos, matRot, modelHandle, CockpitRearSeat);
	bullet->Init();

	//SetMousePoint(WindowX / 2, WindowY / 2);
	//visible = false;

}

void Player::Update(float deltaTime)
{
	// ƒXƒP[ƒ‹.
	mat = MGetIdent();// ‡@.

	// ‰ñ“].
	Rotate(deltaTime);

	// ˆÚ“®.
	Movement(deltaTime);

	// ”½‰f.
	MV1SetMatrix(modelHandle, mat);
	
	// ƒ[ƒ^[‚Ì‰ñ“].
	RotorRotate(deltaTime);

	// ŽËŒ‚.
	BulletFire(deltaTime);

	// ƒJƒƒ‰.
	camera->Update(MV1GetFramePosition(modelHandle, 1), matRot);
	//GetTransMat(MV1GetFrameLocalWorldMatrix(modelHandle, CockpitFrontSeat))
	

}

void Player::Rotate(float deltaTime)
{
#if 1
	// ƒˆ[.
	bool yawFlag = false;
	if (CheckHitKey(KEY_INPUT_E))
	{
		yaw += YawAccelAndDecel;
		yawFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		yaw -= YawAccelAndDecel;
		yawFlag = true;
	}
	if (yaw > MaxYawSpeed || yaw < -MaxYawSpeed)
	{
		yaw = MaxYawSpeed * ((yaw < 0) ? -1.0f : 1.0f);
	}
	if (!yawFlag)
	{
		yaw = 0.0f;
	}

	// ƒsƒbƒ`.
	bool pitchFlag = false;
	if (CheckHitKey(KEY_INPUT_W))
	{
		pitch -= PitchAccelAndDecel;
		pitchFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		pitch += PitchAccelAndDecel;
		pitchFlag = true;
	}
	if (pitch > MaxPichSpeed || pitch < -MaxPichSpeed)
	{
		pitch = MaxPichSpeed * ((pitch < 0) ? -1.0f : 1.0f);
	}
	if (!pitchFlag) 
	{
		pitch = 0.0f;
	}

	// ƒ[ƒ‹. 
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
	if (roll > MaxRollSpeed || roll < -MaxRollSpeed)// Å‘å‰ñ“]‘¬“x‚ð’´‚¦‚È‚¢‚æ‚¤‚É.
	{
		roll = MaxRollSpeed * ((roll > 0) ? 1.0f : -1.0f);
	}
	if (!rollFlag)
	{
	//http://www7.plala.or.jp/kfb/program/stg2dvec.html
		/*if (!IsNearAngle(VGet(0,1,0), ToYAxis(mat)))
		{
			
		}*/
		roll = 0.0f;

	}
#else
	
	const int WindowCenterX = WindowX / 2;
	const int WindowCenterY = WindowY / 2;
	int mouseX = 0;
	int mouseY = 0;
	GetMousePoint(&mouseX, &mouseY);
	valiable[0] = WindowCenterX - mouseX;
	valiable[1] = WindowCenterY - mouseY;
	roll = (WindowCenterX - mouseX) * mouseSensitivity;
	if (roll > MaxRollSpeed || roll < -MaxRollSpeed)// Å‘å‰ñ“]‘¬“x‚ð’´‚¦‚È‚¢‚æ‚¤‚É.
	{
		roll = MaxRollSpeed * ((roll > 0) ? 1.0f : -1.0f);
	}

	pitch = (mouseY - WindowCenterY) * mouseSensitivity;
	if (pitch > MaxPichSpeed || pitch < -MaxPichSpeed)
	{
		pitch = MaxPichSpeed * ((pitch < 0) ? -1.0f : 1.0f);
	}
	
	SetMousePoint(WindowCenterX, WindowCenterY);

	bool yawFlag = false;
	if (CheckHitKey(KEY_INPUT_A))
	{
		yaw -= YawAccelAndDecel;
		yawFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		yaw += YawAccelAndDecel;
		yawFlag = true;
	}
	if (yaw > MaxYawSpeed || yaw < -MaxYawSpeed)
	{
		yaw = MaxYawSpeed * ((yaw < 0) ? -1.0f : 1.0f);
	}
	if (!yawFlag)
	{
		yaw = 0.0f;
	}
#endif
	//valiable = deltaTime;
	// ƒNƒH[ƒ^ƒjƒIƒ“‚©‚ç‰ñ“]s—ñ‚É•ÏŠ·.
	VECTOR yAxis = ToYAxis(matRot);// yaw.
	quat = quat * CreateRotationQuaternion(ToRadian(yaw) * deltaTime, yAxis);
	VECTOR xAxis = ToXAxis(matRot);// pitch.
	quat = quat * CreateRotationQuaternion(ToRadian(pitch) * deltaTime, xAxis);
	VECTOR zAxis = ToZAxis(matRot);// roll.
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
	mat = MMult(mat, matRot);// ‡A.
}

void Player::Movement(float deltaTime)
{
	// ‰Á‘¬.
#if 1
	power = 0;
	if (CheckHitKey(KEY_INPUT_LSHIFT) && power <= 100)
	{
		power = 50;
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
	if (CheckHitKey(KEY_INPUT_W) && power <= 100)
	{
		power = 100;
	}
	else
	{
		if (power > 0)
		{
			power -= 10;
		}
		if (pos.y > 0)
		{
			gVelo -= G * deltaTime;
		}
	}
	if (CheckHitKey(KEY_INPUT_S) && power >= 0)
	{
		power = -100;
	}
	// Œ¸‘¬.
	
#endif	

	// ”½‰f.
	velocity = VNorm(ToYAxis(matRot)) * power;
	velocity.y -= G;
	prePos += velocity * deltaTime;
	if (prePos.y <= 0)
	{
		prePos.y = 0;
	}
	pos = prePos;
	matTrans = MGetTranslate(pos);
	mat = MMult(mat, matTrans);// ‡B.
}

void Player::BulletFire(float deltaTime)
{
	intervalTime -= deltaTime;
	if (intervalTime <= 0 && CheckHitKey(KEY_INPUT_SPACE))
	{
		bullet->Generater(modelHandle, MissilepodL, matRot);
		bullet->Generater(modelHandle, MissilepodR, matRot);
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
	const int white = GetColor(255, 255, 255);
	if (camera->IsModelDraw())
	{
		MV1DrawModel(modelHandle);

	}
	DrawFormatString(0, 0, white, "%f:%f:%f", pos.x, pos.y, pos.z);
	DrawFormatString(0, 20, white, "%f:%f:%f",ToYAxis(mat).x, ToYAxis(mat).y, ToYAxis(mat).z);

	camera->Draw(pos, matRot, velocity);
	camera->DebagDraw();
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

