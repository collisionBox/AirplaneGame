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
	MV1SetScale(modelHandle, VGet(0.05f, 0.05f, 0.05f));
	
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	pos = InitVec;
	dir = VScale(InitVecDir, -1);
	velocity = InitVec;
	upVec = 0.0f;
	power = 100.0f;
	rotateSpeed = 0.0f;

	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Update(float deltaTime)
{
	// ヘリコプターの上下移動を制御
	if (CheckHitKey(KEY_INPUT_UP)) 
	{
		power += 1 * deltaTime;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) 
	{
		power -= deltaTime;
	}
	power = min(max(power, 0), 100);
	float targetRotateSpeed = RotateSpeedMax * (power / 100);
	if (rotateSpeed < targetRotateSpeed)
	{
		rotateSpeed += RotateSpeedAccel;
		if (rotateSpeed >= targetRotateSpeed)
		{
			rotateSpeed = targetRotateSpeed;
		}
	}
	else if (rotateSpeed > targetRotateSpeed)
	{
		rotateSpeed -= RotateSpeedDecel;
		if (rotateSpeed <= targetRotateSpeed)
		{
			rotateSpeed = targetRotateSpeed;
		}
	}
	//// ヘリコプターの前後移動を制御
	//if (CheckHitKey(KEY_INPUT_W)) m_velocity += m_direction * m_speed * deltaTime;
	//if (CheckHitKey(KEY_INPUT_S)) m_velocity -= m_direction * m_speed * deltaTime;

	//// ヘリコプターの左右移動を制御
	//if (CheckHitKey(KEY_INPUT_A)) m_velocity += m_right * m_speed * deltaTime;
	//if (CheckHitKey(KEY_INPUT_D)) m_velocity -= m_right * m_speed * deltaTime;

	//// 空気抵抗による減速
	//m_velocity -= m_velocity * m_drag * deltaTime;

	//// 重力による加速度
	//m_velocity += m_gravity * deltaTime;

	//// ヘリコプターの位置を更新
	//m_position += m_velocity * deltaTime;

	//// ヘリコプターの向きに合わせて移動方向を更新
	//m_direction = Quaternion::Rotate(m_rotation) * Vector3(0.0, 0.0, 1.0);
	//m_right = Vector3::Cross(m_direction, Vector3(0.0, 1.0, 0.0)).Normalize();
	うごかない　パワーは初期化で１００にしてるから計算をステップインて確認するべし
	// 空気抵抗の計算
	VECTOR airResistance = VScale(velocity, -1) * dragCoefficient * VSize(velocity);
	
	// ローターの力の計算
	VECTOR rotorDirection =VNorm(VCross(orientation, VGet(0.0f, 1.0f, 0.0f)));
	VECTOR rotorForceVector = rotorDirection * rotorForce;

	// ローターのトルクの計算
	VECTOR rotorTorqueVector = rotorDirection * rotorTorque;

	// 重力の計算
	VECTOR gravity = VGet(0.0, -G * Mass, 0.0);

	// 揚力の計算
	float cl = velocity.y / (0.5 * AirDensity * (rotateSpeed * rotateSpeed) * RotorArra);//揚力係数.
	float l = 0.5 * AirDensity * (rotateSpeed * rotateSpeed) * BradeArea * cl;// 揚力.
	float lengthSquared = velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z;
	VECTOR lift = VGet(0.0, cl * lengthSquared, 0.0);//cl or liftCoefficient.	
	VECTOR up = VGet(0.0f, l, 0.0f);
	float t = EnginPower / rotateSpeed;// 推力.
	float f = l * t;
	// 加速度の計算
	//acceleration = Division((airResistance + rotorForceVector + gravity + lift), Mass);
	acceleration = Division((airResistance + rotorForceVector + gravity + up), Mass);
	// 速度の計算
	velocity += acceleration * deltaTime;
	// 位置の計算
	pos += velocity * deltaTime;
	// 回転の計算
	VECTOR angularAcceleration = Division(rotorTorqueVector, momentOfInertia);
	MATRIX rotMat = MGetRotAxis(rotorDirection, VSize(angularAcceleration) * deltaTime);
	orientation = VTransform(orientation, rotMat);

}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
	DrawFormatString(10, 0, GetColor(255, 255, 255), "%f", power);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

//------------------------------------------------------------------------------
// @brief 迎角(ピッチ角)を算出.
//------------------------------------------------------------------------------
float Player::CalculateAoA()
{
	return ToRadian(atan2f(velocity.y, velocity.z));
}

//------------------------------------------------------------------------------
// @brief 揚力係数の算出.
//------------------------------------------------------------------------------
float Player::CalculateCL()
{
	
	return CalculateAoA() * 0.1f;
}
//------------------------------------------------------------------------------
// @brief 迎角から抗力係数を算出.
//------------------------------------------------------------------------------
float Player::CalculataCD()
{
	return min(max(0.005f + pow(abs(CalculateAoA()) * 0.0315f, 5.0f), 0), 1);
	
}
//------------------------------------------------------------------------------
// @brief 揚力ベクトル算出.
//------------------------------------------------------------------------------
VECTOR Player::CalculateLiftVec()
{
	return VNorm(VCross(VCross(velocity, dir), velocity));
}

//------------------------------------------------------------------------------
// @brief  揚力・抗力を算出.
//------------------------------------------------------------------------------
float Player::CalculateLiftOrDrag(float coefficient, float surface, float velocity, float airDensity)
{
	float q = 0.5f * (velocity * velocity) * airDensity;	//動圧

	return q * surface * coefficient;
}
