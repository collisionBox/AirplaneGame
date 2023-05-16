#pragma once
#include "DxLib.h"
#include "Bullet.h"
class BulletManager
{
public:
	BulletManager(ObjectTag userTag);
	~BulletManager();
	void Init();
	void Generater(VECTOR pos, VECTOR dir);

private:
	const int MaxBulletNum = 20;// 弾の同時処理最大数.
	Bullet* bullet[20];


};

