#include "CameraManager.h"
#include "HUDCamera.h"
#include "TPCamera.h"
CameraManager::CameraManager()
{
	camera[0] = new TPCamera;
	camera[1] = new HUDCamera;
	inputFlag = false;
	cameraNum = 0;
}
void CameraManager::Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)
{
	
	for (pair<int,CameraBase*> ver : camera)
	{
		ver.second->Init(pos, matRot, modelHandle, frameIndex);
	}

	inputFlag = false;
	modelVisible = true;
	cameraNum = 0;
}

void CameraManager::Update(VECTOR pos, MATRIX matRot, float deltaTime)
{
	
	if (CheckHitKey(KEY_INPUT_V))
	{
		if (!inputFlag)
		{
			cameraNum++;
			if (cameraNum > camera.size() - 1)
			{
				cameraNum = 0;
			}
			if (cameraNum == 1)
			{
				modelVisible = false;
			}
			else
			{
				modelVisible = true;
			}
		}
		
		inputFlag = true;
	}
	else
	{
		inputFlag = false;
	}
	camera[cameraNum]->Update(pos, matRot, deltaTime);
}

void CameraManager::Draw(VECTOR pos, MATRIX matRot, VECTOR velocity)
{
	camera[cameraNum]->Draw(pos, matRot, velocity);
}

void CameraManager::DebagDraw()
{
	camera[cameraNum]->DebagDraw();
}
