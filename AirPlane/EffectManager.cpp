#include "EffectManager.h"
#include "EffekseerForDXLib.h"

EffectManager* EffectManager::Instance = nullptr;

EffectManager::EffectManager() :
	effects()
{
	Instance =  nullptr;
}

EffectManager::~EffectManager()
{
	ReleseAllEffect();
}

void EffectManager::Initialize()
{
	if (!Instance)
	{
		Instance = new EffectManager();
	}
}

void EffectManager::Entry(EffectBase* newEffect)
{
	Instance->pendingEffect.push_back(newEffect);
}

void EffectManager::Relese(EffectBase* releseEffevct)
{

	// ペンディングオブジェクト内から検索.
	auto iter = find(Instance->pendingEffect.begin(), Instance->pendingEffect.end(), releseEffevct);
	if (iter != Instance->pendingEffect.end())
	{
		// 見つけたオブジェクトを最後尾に移動してデータを消す.
		iter_swap(iter, Instance->pendingEffect.end() - 1);
		Instance->pendingEffect.pop_back();
		return;
	}
	// 解放オブジェクトのタグ種類を得る.
	EffectTag tag = releseEffevct->GetTag();

	// アクティブオブジェクト内から削除Objectを検索.
	iter = find(Instance->effects[tag].begin(), Instance->effects[tag].end(), releseEffevct);
	if (iter != Instance->effects[tag].end())
	{
		// 見つけたオブジェクトを末尾に移動し、削除.
		iter_swap(iter, Instance->effects[tag].end() - 1);
		delete Instance->effects[tag].back();
	}
}

void EffectManager::ReleseAllEffect()
{
	// 末尾からペンディングオブジェクトをすべてを削除
	while (!Instance->pendingEffect.empty())
	{

		delete Instance->pendingEffect.back();
		Instance->pendingEffect.pop_back();
	}

	// すべてのアクティブオブジェクトを削除
	for (auto& tag : EffectTagAll)
	{
		// 末尾から削除
		while (!Instance->effects[tag].empty())
		{
			delete Instance->effects[tag].back();
			Instance->effects[tag].pop_back();
		}
	}
}

void EffectManager::Update(float deltaTime)
{
	// すべてのアクターの更新
	for (auto& tag : EffectTagAll)
	{
		// 該当タグにあるすべてのオブジェクトを更新
		for (int i = 0; i < Instance->effects[tag].size(); ++i)
		{
			Instance->effects[tag][i]->Update(deltaTime);
		}
	}
	// ペンディング中のオブジェクトをアクティブリストに追加
	for (auto pending : Instance->pendingEffect)
	{
		EffectTag tag = pending->GetTag();
		Instance->effects[tag].emplace_back(pending);
	}
	Instance->pendingEffect.clear();

	// すべてのアクター中で死んでいるアクターをdeadObjectへ一時保管
	vector<EffectBase*> deadObject;
	for (auto& tag : EffectTagAll)
	{
		//deadObjectに移動
		for (auto obj : Instance->effects[tag])
		{
			if (!obj->GetValid())
			{
				deadObject.emplace_back(obj);
			}
		}
		Instance->effects[tag].erase(remove_if(begin(Instance->effects[tag]), end(Instance->effects[tag]), [](EffectBase* b) { return !b->GetValid(); }), cend(Instance->effects[tag]));

	}

	// 死んでいるオブジェクトをdelete
	while (!deadObject.empty())
	{
		delete deadObject.back();
		deadObject.pop_back();
	}
}

void EffectManager::Draw()
{
	for (auto& tag : EffectTagAll)
	{
		if (tag == EffectTag::Graphic)
		{
			for (int i = 0; i < Instance->effects[tag].size(); ++i)
			{
				// 描画可能なオブジェクトのみ描画.
				if (Instance->effects[tag][i]->GetValid())
				{
					DrawEffekseer3D_Begin();
					Instance->effects[tag][i]->Draw();
					DrawEffekseer3D_End();
				}
			}
		}
		else if (tag == EffectTag::Sound)
		{

		}
		
	}
	
}

void EffectManager::Finalize()
{
	ReleseAllEffect();
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
