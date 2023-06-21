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
	void Generater(int modelHandle, int frameIndex, MATRIX matDir);

private:
	const int MaxBulletNum = 50;// 弾の同時処理最大数.
	vector<Bullet*> bullet;

};

