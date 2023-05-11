#include "PlayerCamera.h"
#include "ObjectManager.h"
PlayerCamera::PlayerCamera() : 
	ObjectBase(ObjectTag::Camera)
{
	pos = VGet(0.0f, 10.0f, -20.0f);
	dir = VGet(0.0f, 0.0f, 1.0f);
	targetPos = VAdd(pos, VScale(dir, len));

	SetCameraPositionAndTarget_UpVecY(pos, targetPos);
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(float deltaTime)
{
	
	
}
