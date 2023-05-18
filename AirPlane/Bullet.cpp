#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"


Bullet::Bullet(ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.01f, 0.01f, 0.01f));// サイズの変更.
	myTag = userTag;
	velocity = InitVec;
	visible = false;
	permitUpdate = false;

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

void Bullet::Init(VECTOR pos, VECTOR dir)
{
	// 変数の初期化.
	this->dir = dir;
	this->pos = pos + (dir * PosCorrectionScale);
	velocity = InitVec;
	visible = false;
	permitUpdate = false;
	timeCount = DeadTime;
	CollisionUpdate();

}

void Bullet::Update(float deltaTime)
{
	velocity = dir * Speed * deltaTime;
	prePos += velocity;
	CollisionUpdate(prePos);
	//pos = prePos;
	// 位置の更新.
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	timeCount -= deltaTime;
	if (timeCount <= 0)
	{
		visible = false;
		permitUpdate = false;
	}
}

void Bullet::Generate(VECTOR pos, MATRIX matDir)
{
	this->dir = ToZAxis(matDir);// 傾きがおかしい　ロールてヨーすると
	this->pos = pos;
	this->pos += ToXAxis(matDir) * PosCorrectionScale.x;
	this->pos += ToYAxis(matDir) * PosCorrectionScale.y;
	this->pos += ToZAxis(matDir) * PosCorrectionScale.z;
	timeCount = DeadTime;
	visible = true;
	permitUpdate = true;
	CollisionUpdate();
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 20, white, "%f,%f,%f", pos.x, pos.y, pos.z);

	DrawCollider();
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
}