#include "AssetManager.h"
#include "Math.h"


AssetManager* AssetManager::Instance = nullptr;

AssetManager::AssetManager()
{
	Instance = nullptr;
}

AssetManager::~AssetManager()
{
	Instance->DeleteAllAsset();
	Instance = nullptr;
}

void AssetManager::Initalize()
{
	if (!Instance)
	{
		Instance = new AssetManager;
		 
	}
}

int AssetManager::GetMesh(string meshFileName)
{
	int meshID = 0;
	// 連想配列から以前登録されていないか調べる.
	auto iter = Instance->meshMap.find(meshFileName);

	// 見つからなければ登録
	if (iter == Instance->meshMap.end())
	{
		meshID = MV1LoadModel(meshFileName.c_str());
		if (meshID == -1)
		{
			printfDx("model load faild[%s]", meshFileName.c_str());
			return meshID;
		}
		Instance->meshMap.emplace(meshFileName, meshID);
	}

	meshID = MV1DuplicateModel(Instance->meshMap[meshFileName]);
	Instance->duplicateMesh.push_back(meshID);
	return meshID;
	

}

void AssetManager::DeleteMesh(int meshID)
{
	// Duplicateの中でメッシュを検索し、削除.
	auto iter = find(Instance->duplicateMesh.begin(), Instance->duplicateMesh.end(), meshID);
	if (iter == Instance->duplicateMesh.end())
	{
		// 未発見.
		return;
	}

	MV1DeleteModel(meshID);

	// 末尾のデータと入れ替えて末尾を削除.
	iter_swap(iter, Instance->duplicateMesh.end() - 1);
	Instance->duplicateMesh.pop_back();
}

void AssetManager::DeleteAllAsset()
{
	for (auto iter = Instance->meshMap.begin(); iter != Instance->meshMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	for (auto iter = Instance->duplicateMesh.begin(); iter != Instance->duplicateMesh.end(); ++iter)
	{
		MV1DeleteModel(*iter);
	}

	Instance->meshMap.clear();
	Instance->duplicateMesh.clear();

}

MATRIX AssetManager::GetFrameRotateMatrix(int modelHandle, int frameIndelx, float modelScale, float rotXAxsis, float rotYAxsis, float rotZAxsis, VECTOR xAxis, VECTOR yAxis, VECTOR zAxis)
{
	// 親フレームの取得.
	int parentFrame = MV1GetFrameParent(modelHandle, frameIndelx);
	// モデルの拡大率にしたがって移動距離を補正する準備.
	if (modelScale == 0)
	{
		return MGetIdent();
	}
	else
	{
		modelScale = 1 / modelScale;
	}
	// 親フレームが存在するなら相対座標分だけ平衡移動する行列を取得.
	MATRIX matTrans;
	if (parentFrame != -2)
	{
		//親子フレームの座標の取得.
		VECTOR parentVec = MV1GetFramePosition(modelHandle, parentFrame);
		VECTOR childVec = MV1GetFramePosition(modelHandle, frameIndelx);//　ワールド座標軸で回転してるからローカル座標軸に変更

		// 親を基準にした子の相対座標を取得.
		VECTOR rerativPar2chi = VSub(childVec, parentVec);
		// モデルの拡大率によって相対距離を修正.
		rerativPar2chi = VScale(rerativPar2chi, modelScale);
		matTrans = MGetTranslate(rerativPar2chi);

	}
	else
	{
		matTrans = MGetIdent();
	}
	// それぞれの軸に沿って回転する行列を取得.
	MATRIX matXAxis = MGetRotAxis(xAxis, rotXAxsis);
	MATRIX matYAxis = MGetRotAxis(yAxis, rotYAxsis);
	MATRIX matZAxis = MGetRotAxis(zAxis, rotZAxsis);

	// 遡って親フレームの回転要素を取得.
	vector<MATRIX> matParentsRotates;
	while (-2 != parentFrame && -1 != parentFrame)
	{
		// 親フレームの座標を取得し、そこから回転要素を抽出.
		MATRIX matParentFrame = MV1GetFrameLocalMatrix(modelHandle, parentFrame);
		MATRIX matParentRotate = MGetRotElem(matParentFrame);
		// 回転行列の逆行列　＝　回転の方向を逆にする.
		MATRIX matParentRoateInv = MInverse(matParentRotate);
		// 順に追加.
		matParentsRotates.push_back(matParentRoateInv);

		// 親のフレームを追加取得.
		parentFrame = MV1GetFrameParent(modelHandle, parentFrame);

	}
	// 取得した祖先たちの回転行列をより中枢のほうからかけて、平行移動のベクトルを補正する.
	for (int i = matParentsRotates.size() - 1; i >= 0; i--)
	{
		matTrans = MMult(matTrans, matParentsRotates[i]);
	}

	// 平行移動ベクトルに生じうる回転成分を消す.
	matTrans.m[0][0] = 1; matTrans.m[0][1] = 0; matTrans.m[0][2] = 0;
	matTrans.m[1][0] = 0; matTrans.m[1][1] = 1; matTrans.m[1][2] = 0;
	matTrans.m[2][0] = 0; matTrans.m[2][1] = 0; matTrans.m[2][2] = 1;

	// 軸毎に回転させてから平行移動を実行する.
	MATRIX matReturn = MMult(MMult(MMult(matXAxis, matYAxis), matZAxis), matTrans);

	return matReturn;
}

MATRIX AssetManager::MV1GetFrameRotateMatrix(int modelHandle, int frameIndelx, float rotXAxsis, float rotYAxsis, float rotZAxsis, float modelScale)
{
	// 親フレームの取得.
	int parentFrame = MV1GetFrameParent(modelHandle, frameIndelx);

	// モデルの拡大率にしたがって移動距離を補正する準備.
	if (modelScale == 0)
	{
		return MGetIdent();
	}
	else
	{
		modelScale = 1 / modelScale;
	}


	// 相対座標分の平行移動行列を取得.
	MATRIX matTrans;
	if (parentFrame != -2)
	{
		//親子フレームの座標の取得.
		VECTOR parentVec = MV1GetFramePosition(modelHandle, parentFrame);
		VECTOR childVec = MV1GetFramePosition(modelHandle, frameIndelx);//　ワールド座標軸で回転してるからローカル座標軸に変更

		// 親を基準にした子の相対座標を取得.
		VECTOR rerativPar2chi = VSub(childVec, parentVec);
		// モデルの拡大率によって相対距離を修正.
		rerativPar2chi = VScale(rerativPar2chi, modelScale);
		matTrans = MGetTranslate(rerativPar2chi);

	}
	else
	{
		matTrans = MGetIdent();
	}


	// それぞれの軸に沿って回転する行列を取得.
	MATRIX matXAxis = MGetRotX(rotXAxsis);
	MATRIX matYAxis = MGetRotY(rotYAxsis);
	MATRIX matZAxis = MGetRotZ(rotZAxsis);

	// 遡って親フレームの回転要素を取得.
	vector<MATRIX> matParentsRotates;
	while (-2 != parentFrame && -1 != parentFrame)
	{
		// 親フレームの座標を取得し、そこから回転要素を抽出.
		MATRIX matParentFrame = MV1GetFrameLocalMatrix(modelHandle, parentFrame);
		MATRIX matParentRotate = MGetRotElem(matParentFrame);
		// 回転行列の逆行列　＝　回転の方向を逆にする.
		MATRIX matParentRoateInv = MInverse(matParentRotate);
		// 順に追加.
		matParentsRotates.push_back(matParentRoateInv);

		// 親のフレームを追加取得.
		parentFrame = MV1GetFrameParent(modelHandle, parentFrame);

	}
	// 取得した祖先たちの回転行列をより中枢のほうからかけて、平行移動のベクトルを補正する.
	for (int i = matParentsRotates.size() - 1; i >= 0; i--)
	{
		matTrans = MMult(matTrans, matParentsRotates[i]);
	}

	// 平行移動ベクトルに生じうる回転成分を消す.
	matTrans.m[0][0] = 1; matTrans.m[0][1] = 0; matTrans.m[0][2] = 0;
	matTrans.m[1][0] = 0; matTrans.m[1][1] = 1; matTrans.m[1][2] = 0;
	matTrans.m[2][0] = 0; matTrans.m[2][1] = 0; matTrans.m[2][2] = 1;

	// 軸毎に回転させてから平行移動を実行する.
	MATRIX matReturn = MMult(MMult(MMult(matXAxis, matYAxis), matZAxis), matTrans);

	return matReturn;
}

void AssetManager::Finalize()
{
	DeleteAllAsset();
	if (Instance)
	{
		delete Instance;
	}
}


