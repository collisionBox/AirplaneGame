#include "BulletManager.h"
#include "ObjectManager.h"
BulletManager::BulletManager(ObjectTag userTag)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullet[i] = new Bullet(userTag);
		ObjectManager::Entry(bullet[i]);

	}
}

BulletManager::~BulletManager()
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullet[i]->~Bullet();
		bullet[i] = nullptr;
	}
}

void BulletManager::Init()
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullet[i]->MakePermitUpdateFalse();
	}
}

void BulletManager::Generater(VECTOR pos, VECTOR dir)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		if (!bullet[i]->GetPermitUpdate())
		{
			bullet[i]->Generate(pos, dir);
			break;
		}
	}
}
