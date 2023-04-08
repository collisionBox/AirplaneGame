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
	power = 0.0f;
	rotateSpeed = 0.0f;
	acceleration = InitVec;
	orientation = InitVec;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Update(float deltaTime)
{

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
	DrawFormatString(10, 0, GetColor(255, 255, 255), "%f", power);
	DrawFormatString(10, 20, GetColor(255, 255, 255), "%f%f%f", pos.x, pos.y, pos.z);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "%f%f%f", velocity.x, velocity.y, velocity.z);
	DrawFormatString(10, 60, GetColor(255, 255, 255), "%f%f%f", acceleration);
}

void Player::OnCollisionEnter(const ObjectBase* other)
{
}

//------------------------------------------------------------------------------
// @brief Œ}Šp(ƒsƒbƒ`Šp)‚ğZo.
//------------------------------------------------------------------------------
float Player::CalculateAoA()
{
	return ToRadian(atan2f(velocity.y, velocity.z));
}

//------------------------------------------------------------------------------
// @brief —g—ÍŒW”‚ÌZo.
//------------------------------------------------------------------------------
float Player::CalculateCL()
{
	
	return CalculateAoA() * 0.1f;
}
//------------------------------------------------------------------------------
// @brief Œ}Šp‚©‚çR—ÍŒW”‚ğZo.
//------------------------------------------------------------------------------
float Player::CalculataCD()
{
	return min(max(0.005f + pow(abs(CalculateAoA()) * 0.0315f, 5.0f), 0), 1);
	
}
//------------------------------------------------------------------------------
// @brief —g—ÍƒxƒNƒgƒ‹Zo.
//------------------------------------------------------------------------------
VECTOR Player::CalculateLiftVec()
{
	return VNorm(VCross(VCross(velocity, dir), velocity));
}

//------------------------------------------------------------------------------
// @brief  —g—ÍER—Í‚ğZo.
//------------------------------------------------------------------------------
float Player::CalculateLiftOrDrag(float coefficient, float surface, float velocity, float airDensity)
{
	float q = 0.5f * (velocity * velocity) * airDensity;	//“®ˆ³

	return q * surface * coefficient;
}
