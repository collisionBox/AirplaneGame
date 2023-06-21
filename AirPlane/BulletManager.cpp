#include "BulletManager.h"
#include "ObjectManager.h"
BulletManager::BulletManager(ObjectTag userTag)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullet.push_back(new Bullet(ObjectTag::Player));
		ObjectManager::Entry(bullet[i]);

	}
}

BulletManager::~BulletManager()
{
	for (Bullet* ver : bullet)
	{
		ver->~Bullet();
		ver = nullptr;
	}
}

void BulletManager::Init()
{
	for (Bullet* ver : bullet)
	{
		ver->Init();
	}
}

void BulletManager::Generater(int modelHandle, int frameIndex, MATRIX matDir)
{
	for (Bullet* ver : bullet)
	{
		if (!ver->GetPermitUpdate())
		{
			ver->Generate(modelHandle, frameIndex, matDir);
			break;
		}
	}
}
