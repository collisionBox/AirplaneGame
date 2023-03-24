#pragma once
#include <unordered_map>
#include <vector>
#include "EffectBase.h"
#include "EffectTag.h"

using namespace std;
/// <summary>
/// 演出用マネージャー.
/// </summary>
class EffectManager
{
public:

	static void Initialize();

	static void Entry(EffectBase* newEffect);
	static void Relese(EffectBase* releseEffevct);
	static void ReleseAllEffect();

	static void Update(float deltaTime);
	static void Draw();
	static void Finalize();
private:
	EffectManager();
	~EffectManager();
	vector<EffectBase*>pendingEffect;
	unordered_map<EffectTag, vector<EffectBase*>> effects;
	static EffectManager* Instance;
};

