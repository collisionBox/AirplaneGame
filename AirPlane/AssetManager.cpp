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
	// �A�z�z�񂩂�ȑO�o�^����Ă��Ȃ������ׂ�.
	auto iter = Instance->meshMap.find(meshFileName);

	// ������Ȃ���Γo�^
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
	// Duplicate�̒��Ń��b�V�����������A�폜.
	auto iter = find(Instance->duplicateMesh.begin(), Instance->duplicateMesh.end(), meshID);
	if (iter == Instance->duplicateMesh.end())
	{
		// ������.
		return;
	}

	MV1DeleteModel(meshID);

	// �����̃f�[�^�Ɠ���ւ��Ė������폜.
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
	// �e�t���[���̎擾.
	int parentFrame = MV1GetFrameParent(modelHandle, frameIndelx);
	// ���f���̊g�嗦�ɂ��������Ĉړ�������␳���鏀��.
	if (modelScale == 0)
	{
		return MGetIdent();
	}
	else
	{
		modelScale = 1 / modelScale;
	}
	// �e�t���[�������݂���Ȃ瑊�΍��W���������t�ړ�����s����擾.
	MATRIX matTrans;
	if (parentFrame != -2)
	{
		//�e�q�t���[���̍��W�̎擾.
		VECTOR parentVec = MV1GetFramePosition(modelHandle, parentFrame);
		VECTOR childVec = MV1GetFramePosition(modelHandle, frameIndelx);//�@���[���h���W���ŉ�]���Ă邩�烍�[�J�����W���ɕύX

		// �e����ɂ����q�̑��΍��W���擾.
		VECTOR rerativPar2chi = VSub(childVec, parentVec);
		// ���f���̊g�嗦�ɂ���đ��΋������C��.
		rerativPar2chi = VScale(rerativPar2chi, modelScale);
		matTrans = MGetTranslate(rerativPar2chi);

	}
	else
	{
		matTrans = MGetIdent();
	}
	// ���ꂼ��̎��ɉ����ĉ�]����s����擾.
	MATRIX matXAxis = MGetRotAxis(xAxis, rotXAxsis);
	MATRIX matYAxis = MGetRotAxis(yAxis, rotYAxsis);
	MATRIX matZAxis = MGetRotAxis(zAxis, rotZAxsis);

	// �k���Đe�t���[���̉�]�v�f���擾.
	vector<MATRIX> matParentsRotates;
	while (-2 != parentFrame && -1 != parentFrame)
	{
		// �e�t���[���̍��W���擾���A���������]�v�f�𒊏o.
		MATRIX matParentFrame = MV1GetFrameLocalMatrix(modelHandle, parentFrame);
		MATRIX matParentRotate = MGetRotElem(matParentFrame);
		// ��]�s��̋t�s��@���@��]�̕������t�ɂ���.
		MATRIX matParentRoateInv = MInverse(matParentRotate);
		// ���ɒǉ�.
		matParentsRotates.push_back(matParentRoateInv);

		// �e�̃t���[����ǉ��擾.
		parentFrame = MV1GetFrameParent(modelHandle, parentFrame);

	}
	// �擾�����c�悽���̉�]�s�����蒆���̂ق����炩���āA���s�ړ��̃x�N�g����␳����.
	for (int i = matParentsRotates.size() - 1; i >= 0; i--)
	{
		matTrans = MMult(matTrans, matParentsRotates[i]);
	}

	// ���s�ړ��x�N�g���ɐ��������]����������.
	matTrans.m[0][0] = 1; matTrans.m[0][1] = 0; matTrans.m[0][2] = 0;
	matTrans.m[1][0] = 0; matTrans.m[1][1] = 1; matTrans.m[1][2] = 0;
	matTrans.m[2][0] = 0; matTrans.m[2][1] = 0; matTrans.m[2][2] = 1;

	// �����ɉ�]�����Ă��畽�s�ړ������s����.
	MATRIX matReturn = MMult(MMult(MMult(matXAxis, matYAxis), matZAxis), matTrans);

	return matReturn;
}

MATRIX AssetManager::MV1GetFrameRotateMatrix(int modelHandle, int frameIndelx, float rotXAxsis, float rotYAxsis, float rotZAxsis, float modelScale)
{
	// �e�t���[���̎擾.
	int parentFrame = MV1GetFrameParent(modelHandle, frameIndelx);

	// ���f���̊g�嗦�ɂ��������Ĉړ�������␳���鏀��.
	if (modelScale == 0)
	{
		return MGetIdent();
	}
	else
	{
		modelScale = 1 / modelScale;
	}


	// ���΍��W���̕��s�ړ��s����擾.
	MATRIX matTrans;
	if (parentFrame != -2)
	{
		//�e�q�t���[���̍��W�̎擾.
		VECTOR parentVec = MV1GetFramePosition(modelHandle, parentFrame);
		VECTOR childVec = MV1GetFramePosition(modelHandle, frameIndelx);//�@���[���h���W���ŉ�]���Ă邩�烍�[�J�����W���ɕύX

		// �e����ɂ����q�̑��΍��W���擾.
		VECTOR rerativPar2chi = VSub(childVec, parentVec);
		// ���f���̊g�嗦�ɂ���đ��΋������C��.
		rerativPar2chi = VScale(rerativPar2chi, modelScale);
		matTrans = MGetTranslate(rerativPar2chi);

	}
	else
	{
		matTrans = MGetIdent();
	}


	// ���ꂼ��̎��ɉ����ĉ�]����s����擾.
	MATRIX matXAxis = MGetRotX(rotXAxsis);
	MATRIX matYAxis = MGetRotY(rotYAxsis);
	MATRIX matZAxis = MGetRotZ(rotZAxsis);

	// �k���Đe�t���[���̉�]�v�f���擾.
	vector<MATRIX> matParentsRotates;
	while (-2 != parentFrame && -1 != parentFrame)
	{
		// �e�t���[���̍��W���擾���A���������]�v�f�𒊏o.
		MATRIX matParentFrame = MV1GetFrameLocalMatrix(modelHandle, parentFrame);
		MATRIX matParentRotate = MGetRotElem(matParentFrame);
		// ��]�s��̋t�s��@���@��]�̕������t�ɂ���.
		MATRIX matParentRoateInv = MInverse(matParentRotate);
		// ���ɒǉ�.
		matParentsRotates.push_back(matParentRoateInv);

		// �e�̃t���[����ǉ��擾.
		parentFrame = MV1GetFrameParent(modelHandle, parentFrame);

	}
	// �擾�����c�悽���̉�]�s�����蒆���̂ق����炩���āA���s�ړ��̃x�N�g����␳����.
	for (int i = matParentsRotates.size() - 1; i >= 0; i--)
	{
		matTrans = MMult(matTrans, matParentsRotates[i]);
	}

	// ���s�ړ��x�N�g���ɐ��������]����������.
	matTrans.m[0][0] = 1; matTrans.m[0][1] = 0; matTrans.m[0][2] = 0;
	matTrans.m[1][0] = 0; matTrans.m[1][1] = 1; matTrans.m[1][2] = 0;
	matTrans.m[2][0] = 0; matTrans.m[2][1] = 0; matTrans.m[2][2] = 1;

	// �����ɉ�]�����Ă��畽�s�ړ������s����.
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


