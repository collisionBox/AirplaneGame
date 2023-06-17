#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"
#include "HUDCamera.h"

Bullet::Bullet(ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));// サイズの変更.
	myTag = userTag;
	Init();
	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;
	CollisionUpdate();

}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);
	alive = false;
}

void Bullet::Init()
{
	// 変数の初期化.
	visible = false;
	permitUpdate = false;
	this->dir = this->pos = velocity = InitVec;
	timeCount = DeadTime;
	CollisionUpdate();
}

void Bullet::Update(float deltaTime)
{
	機体の重力を確認　ターゲットサークルの中に弾を範囲に入れる
	Delete();

	velocity = ToZAxis(matRot) * -Speed * deltaTime;
	velocity.y -= G;
	prePos += velocity;
	CollisionUpdate(prePos);
	pos = prePos;
	// 位置の更新.
	/*MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);*/
	mat = MGetScale(VGet(modelScale, modelScale, modelScale));
	mat = mat * matRot;
	mat = mat * MGetTranslate(pos);
	MV1SetMatrix(modelHandle, mat);

	timeCount -= deltaTime;
	if (timeCount <= 0)
	{
		Init();
	}
}

void Bullet::Generate(int ModelHandle, int frameIndex, MATRIX matDir)
{
	matTrans = MV1GetFrameLocalWorldMatrix(ModelHandle, frameIndex);
	matRot = MGetRotAxis(ToYAxis(matDir), ToRadian(ZeroInAngle));
	pos = M2Pos(matTrans);
	prePos = pos;
	timeCount = DeadTime;
	visible = true;
	permitUpdate = true;
	CollisionUpdate();
	mat = MGetScale(VGet(modelScale, modelScale, modelScale));
	mat = mat * matRot;

	mat = mat * matTrans;
	MV1SetMatrix(modelHandle, mat);
	//MV1SetPosition(modelHandle, this->pos);
	//MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f,%f,%f", dir.x, dir.y, dir.z);

	DrawCollider();
}

float Bullet::CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir)
{
	float a = VSize(airplanePos - this->pos);
	float b = VSize((airplanePos + (ToZAxis(airplaneMatDir) * GunTargetingDistance)) - this->pos);
	float molecule = (GunTargetingDistance * GunTargetingDistance) + (b * b) - (a - a);
	float denominator = 2.0f * GunTargetingDistance * b;
	return molecule / denominator;
}

void Bullet::Delete()
{
	if (pos.y <= 0)
	{
		visible = false;
		permitUpdate = false;
	}
	if (prePos.y <= 0)
	{
		pos.y = 0;
	}
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
}