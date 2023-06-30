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

	prePos = pos = worldVel = InitVec;
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
	// スケール.
	mat = MGetIdent();// ①.

	// 回転.
	Rotate(deltaTime);

	// 移動.
	Movement(deltaTime);

	// 反映.
	MV1SetMatrix(modelHandle, mat);
	
	// ローターの回転.
	RotorRotate(deltaTime);

	// 射撃.
	BulletFire(deltaTime);

	// カメラ.
	camera->Update(MV1GetFramePosition(modelHandle, 1), matRot, deltaTime);
	//GetTransMat(MV1GetFrameLocalWorldMatrix(modelHandle, CockpitFrontSeat))
	

}

void Player::Rotate(float deltaTime)
{
#if 1
	// ヨー.
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
		RotateDecel(yaw, YawAccelAndDecel);
	}

	// ピッチ.
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
		RotateDecel(pitch, PitchAccelAndDecel);
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
	if (roll > MaxRollSpeed || roll < -MaxRollSpeed)// 最大回転速度を超えないように.
	{
		roll = MaxRollSpeed * ((roll > 0) ? 1.0f : -1.0f);
	}
	if (!rollFlag)
	{
		RotateDecel(roll, RollAccelAndDecel);

	}
	// クォータニオンから回転行列に変換.
	VECTOR yAxis = ToYAxis(matRot);// yaw.
	quat = quat * CreateRotationQuaternion(ToRadian(yaw) * deltaTime, yAxis);
	VECTOR xAxis = ToXAxis(matRot);// pitch.
	quat = quat * CreateRotationQuaternion(ToRadian(pitch) * deltaTime, xAxis);
	VECTOR zAxis = ToZAxis(matRot);// roll.
	quat = quat * CreateRotationQuaternion(ToRadian(roll) * deltaTime, zAxis);
	MATRIX matRotVel = QuaternionToMatrix(quat);
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;

#else
	
	const int WindowCenterX = WindowX / 2;
	const int WindowCenterY = WindowY / 2;
	int mouseX = 0;
	int mouseY = 0;
	GetMousePoint(&mouseX, &mouseY);
	valiable[0] = WindowCenterX - mouseX;
	valiable[1] = WindowCenterY - mouseY;

	float pitchAmount = (WindowCenterY - mouseY) * mouseSensitivity;
	float yawAmount = (WindowCenterX - mouseX) * mouseSensitivity;

	bool pitchFlag = false;
	if (abs(pitch) <= abs(pitchAmount))
	{
		if (pitchAmount > 0)
		{
			pitch += PitchAccelAndDecel;
			pitchFlag = true;
		}
		else if (pitchAmount < 0)
		{
			pitch -= PitchAccelAndDecel;
			pitchFlag = true;
		}
	}
	if (pitch > MaxPichSpeed || pitch < -MaxPichSpeed)
	{
		pitch = MaxPichSpeed * ((pitch > 0) ? 1.0f : -1.0f);
	}
	if (!pitchFlag)
	{
		RotateDecel(pitch, PitchAccelAndDecel);
	}

	bool yawFlag = false;
	if (abs(yaw) <= abs(yawAmount))
	{
		if (yawAmount < 0)
		{
			yaw += YawAccelAndDecel;
			yawFlag = true;
		}
		else if (yawAmount > 0)
		{
			yaw -= YawAccelAndDecel;
			yawFlag = true;
		}
	}
	
	if (yaw > MaxYawSpeed || yaw < -MaxYawSpeed)
	{
		yaw = MaxYawSpeed * ((yaw < 0) ? -1.0f : 1.0f);
	}
	if (!yawFlag)
	{
		RotateDecel(yaw, YawAccelAndDecel);
	}

	SetMousePoint(WindowCenterX, WindowCenterY);

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
	if (roll > MaxRollSpeed || roll < -MaxRollSpeed)// 最大回転速度を超えないように.
	{
		roll = MaxRollSpeed * ((roll > 0) ? 1.0f : -1.0f);
	}
	if (!rollFlag)
	{
		RotateDecel(roll, RollAccelAndDecel);
	}

	// クォータニオンから回転行列に変換.
	VECTOR yAxis = VGet(0.0f, 1.0f, 0.0f);// yaw.
	quat = quat * CreateRotationQuaternion(ToRadian(yaw) * deltaTime, yAxis);
	VECTOR xAxis = ToXAxis(matRot);// pitch.
	quat = quat * CreateRotationQuaternion(ToRadian(pitch) * deltaTime, xAxis);
	VECTOR zAxis = ToZAxis(matRot);// roll.
	quat = quat * CreateRotationQuaternion(ToRadian(roll) * deltaTime, zAxis);
	MATRIX matRotVel = QuaternionToMatrix(quat);
	quat.x = quat.y = quat.z = 0.0f;
	quat.t = 1.0f;

#endif
	//valiable = deltaTime;

	if (prePos.y <= 0.0f)
	{ 

	}
	if (!rollFlag && roll == 0.0f)
	{
	}

	
	if (CheckHitKey(KEY_INPUT_P))
	{
		//matRotVel = (MInverse(MGetRotVec2(VGet(0.0f, 1.0f, 0.0f), ToYAxis(matRot))));
	}
	matRot = MMult(matRot, matRotVel);
	mat = MMult(mat, matRot);// ②.
}

void Player::RotateDecel(float& axis, float deceleration)
{
	if (axis < 0)
	{
		axis += deceleration;
	}
	else if(axis > 0)
	{
		axis -= deceleration;
	}

	if (axis <= deceleration && axis >= deceleration)
	{
		axis = 0;
	}

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
	}
	if (CheckHitKey(KEY_INPUT_S) && power >= 0)
	{
		power = -100;
	}
	// 減速.
	
#endif	

	// 反映.
	velocity = VNorm(ToYAxis(matRot)) * power;
	velocity.y -= G;
	worldVel += velocity;
	prePos += velocity * deltaTime;
	if (prePos.y <= 0)
	{
		prePos.y = 0;
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
	if (rotateNum >= 360.0f)
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
	DrawFormatString(0, 20, white, "p:%f r:%f y:%f", ToYAxis(matRot).x, ToYAxis(matRot).y, ToYAxis(matRot).z);
	DrawFormatString(0, 120, white, "p:%f r:%f y:%f",qwe.x, qwe.y, qwe.z);
	DrawLine3D(pos, ToZAxis(matRot) * -200, GetColor(255, 0, 0));
	DrawLine3D(pos, ToXAxis(matRot) * -200, GetColor(0, 255, 0));
	DrawLine3D(pos, ToYAxis(matRot) * 200, GetColor(0, 0, 255));
	VECTOR holizon = ToXAxis(matRot);
	holizon.x = abs(holizon.x) * ((holizon.y > 0.0f) ? -1.0f : 1.0f);
	holizon.z = abs(holizon.z) * ((holizon.y > 0.0f) ? -1.0f : 1.0f);
	holizon.y = 0.0f;
	DrawLine3D(InitVec, InitVec + (holizon * 200), GetColor(255, 0, 255));
	camera->Draw(pos, matRot, velocity);
	camera->DebagDraw();
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

