#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"


Bullet::Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// サイズの変更.
	myTag = userTag;

	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;
	CollisionUpdate();

}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);

}

void Bullet::Init(VECTOR pos, VECTOR dir)
{
	// 変数の初期化.
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullet[i].aliveFlag = false;
		bullet[i].mh = modelHandle;
		bullet[i].pos = bullet[i].prePos =
			bullet[i].dir = bullet[i].velocity = InitVec;
		
	}
	
}

void Bullet::Update(float deltaTime)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		if (bullet[i].aliveFlag)
		{
			bullet[i].velocity += dir * Speed;
			bullet[i].prePos += bullet[i].velocity * deltaTime;
		}
		CollisionUpdate(prePos);
		if (bullet[i].aliveFlag)
		{
			bullet[i].pos = prePos;
		}
	}

	// 位置の更新.
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}

void Bullet::Generate(VECTOR pos, VECTOR dir)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		if (!bullet[i].aliveFlag)
		{
			bullet[i].pos = pos;
			bullet[i].dir = dir;
			bullet[i].aliveFlag = true;
			MV1SetPosition(modelHandle, bullet[i].pos);
			MV1SetRotationZYAxis(modelHandle, bullet[i].dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
			break;
		}
		

	}
}


void Bullet::Draw()
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		if (bullet[i].aliveFlag)
		{
			MV1DrawModel(bullet[i].mh);
			DrawCollider();
		}
		

	}
	
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
}