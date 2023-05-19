#pragma once
#include "DxLib.h"
#include "Bullet.h"
#include <vector>
using namespace std;
class BulletManager
{
public:
	BulletManager(ObjectTag userTag);
	~BulletManager();
	void Init();
	void Generater(VECTOR pos, MATRIX matDir);

private:
	const int MaxBulletNum = 30;// �e�̓��������ő吔.
	vector<Bullet*> bullet;
	int bulletCounter;

};

