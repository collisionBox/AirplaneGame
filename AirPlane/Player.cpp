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
	// �w���R�v�^�[�̏㉺�ړ��𐧌�
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
	//// �w���R�v�^�[�̑O��ړ��𐧌�
	//if (CheckHitKey(KEY_INPUT_W)) m_velocity += m_direction * m_speed * deltaTime;
	//if (CheckHitKey(KEY_INPUT_S)) m_velocity -= m_direction * m_speed * deltaTime;

	//// �w���R�v�^�[�̍��E�ړ��𐧌�
	//if (CheckHitKey(KEY_INPUT_A)) m_velocity += m_right * m_speed * deltaTime;
	//if (CheckHitKey(KEY_INPUT_D)) m_velocity -= m_right * m_speed * deltaTime;

	//// ��C��R�ɂ�錸��
	//m_velocity -= m_velocity * m_drag * deltaTime;

	//// �d�͂ɂ������x
	//m_velocity += m_gravity * deltaTime;

	//// �w���R�v�^�[�̈ʒu���X�V
	//m_position += m_velocity * deltaTime;

	//// �w���R�v�^�[�̌����ɍ��킹�Ĉړ��������X�V
	//m_direction = Quaternion::Rotate(m_rotation) * Vector3(0.0, 0.0, 1.0);
	//m_right = Vector3::Cross(m_direction, Vector3(0.0, 1.0, 0.0)).Normalize();
	�������Ȃ��@�p���[�͏������łP�O�O�ɂ��Ă邩��v�Z���X�e�b�v�C���Ċm�F����ׂ�
	// ��C��R�̌v�Z
	VECTOR airResistance = VScale(velocity, -1) * dragCoefficient * VSize(velocity);
	
	// ���[�^�[�̗͂̌v�Z
	VECTOR rotorDirection =VNorm(VCross(orientation, VGet(0.0f, 1.0f, 0.0f)));
	VECTOR rotorForceVector = rotorDirection * rotorForce;

	// ���[�^�[�̃g���N�̌v�Z
	VECTOR rotorTorqueVector = rotorDirection * rotorTorque;

	// �d�͂̌v�Z
	VECTOR gravity = VGet(0.0, -G * Mass, 0.0);

	// �g�͂̌v�Z
	float cl = velocity.y / (0.5 * AirDensity * (rotateSpeed * rotateSpeed) * RotorArra);//�g�͌W��.
	float l = 0.5 * AirDensity * (rotateSpeed * rotateSpeed) * BradeArea * cl;// �g��.
	float lengthSquared = velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z;
	VECTOR lift = VGet(0.0, cl * lengthSquared, 0.0);//cl or liftCoefficient.	
	VECTOR up = VGet(0.0f, l, 0.0f);
	float t = EnginPower / rotateSpeed;// ����.
	float f = l * t;
	// �����x�̌v�Z
	//acceleration = Division((airResistance + rotorForceVector + gravity + lift), Mass);
	acceleration = Division((airResistance + rotorForceVector + gravity + up), Mass);
	// ���x�̌v�Z
	velocity += acceleration * deltaTime;
	// �ʒu�̌v�Z
	pos += velocity * deltaTime;
	// ��]�̌v�Z
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
// @brief �}�p(�s�b�`�p)���Z�o.
//------------------------------------------------------------------------------
float Player::CalculateAoA()
{
	return ToRadian(atan2f(velocity.y, velocity.z));
}

//------------------------------------------------------------------------------
// @brief �g�͌W���̎Z�o.
//------------------------------------------------------------------------------
float Player::CalculateCL()
{
	
	return CalculateAoA() * 0.1f;
}
//------------------------------------------------------------------------------
// @brief �}�p����R�͌W�����Z�o.
//------------------------------------------------------------------------------
float Player::CalculataCD()
{
	return min(max(0.005f + pow(abs(CalculateAoA()) * 0.0315f, 5.0f), 0), 1);
	
}
//------------------------------------------------------------------------------
// @brief �g�̓x�N�g���Z�o.
//------------------------------------------------------------------------------
VECTOR Player::CalculateLiftVec()
{
	return VNorm(VCross(VCross(velocity, dir), velocity));
}

//------------------------------------------------------------------------------
// @brief  �g�́E�R�͂��Z�o.
//------------------------------------------------------------------------------
float Player::CalculateLiftOrDrag(float coefficient, float surface, float velocity, float airDensity)
{
	float q = 0.5f * (velocity * velocity) * airDensity;	//����

	return q * surface * coefficient;
}
