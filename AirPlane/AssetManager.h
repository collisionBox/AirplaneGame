#pragma once
#include "DxLib.h"
#include <string>
#include <unordered_map>
#include <atlstr.h>
using namespace std;
class AssetManager final
{
public:
	static void Initalize();// ������.
	static int GetMesh(string meshFileName);// ���b�V���i���f���j�̎擾.
	static void DeleteMesh(int meshID);
	static void DeleteAllAsset();
	static MATRIX GetFrameRotateMatrix(int modelHandle, int frameIndelx, float modelScale, float rotXAxsis, float rotYAxsis, float rotZAxsis, VECTOR xAxis = VGet(1.0f, 0.0f, 0.0f), VECTOR yAxis = VGet(0.0f, 1.0f, 0.0f), VECTOR zAxis = VGet(0.0f, 0.0f, 1.0f));
	static MATRIX MV1GetFrameRotateMatrix(int modelHandle, int frameIndelx, float modelScale, VECTOR rotate);
	// ���b�V���i���f���j�̍폜.
	static void Finalize();// �A�Z�b�g�}�l�[�W���[�̏I������.

private:
	AssetManager();
	~AssetManager();
	static AssetManager* Instance;

	unordered_map<string, int> meshMap;// ���b�V�����{.
	vector<int> duplicateMesh;// ���b�V���𕡐���������

};
//https://qiita.com/Nao-Taka/items/351df30064b38ef64897
