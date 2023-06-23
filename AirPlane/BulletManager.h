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
	const int MaxBulletNum = 55;// ’e‚Ì“¯ˆ—Å‘å”.
	vector<Bullet*> bullet;

};

