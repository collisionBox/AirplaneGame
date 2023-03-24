#include "PlayerCamera.h"
#include "Math.h"

PlayerCamera::PlayerCamera()
{
	Init();
}

void PlayerCamera::Init()
{
	pos = InitVec;
	dir = VGet(0.0f, 0.0f, 1.0f);
    acceleration = 10.0f;
    accel = InitAccel;
    velosity = InitVec;
	roll = 0.0f;
	rollInclement = ToRadian(30.0f);
	length = DefaultLength;

}

void PlayerCamera::Update(float deltaTime)
{

    // ���E�L�[�ŃJ�����̉�]�l��ύX
    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {
        roll -= rollInclement * deltaTime;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {
        roll += rollInclement * deltaTime;
    }

    // �l���傫���Ȃ肷���Ȃ��悤1�������珉��������.
    if (roll > DX_PI_F * 2 || roll < DX_PI_F * -2)
    {
        roll = 0.0f;
    }

    velosity = VScale(dir, accel);
    prePos = VAdd(pos, VScale(velosity, deltaTime));
    pos = prePos;


    // ������� roll �̒l����Z�o
    SetCameraPositionAndTargetAndUpVec(VGet(10.0f, 100.0f, -800.0f), VGet(10.0f, 0.0f, 0.0f), VGet(sin(roll), cos(roll), 0.0f));

}

void PlayerCamera::Input(float deltaTime)
{
}

void PlayerCamera::Draw()
{
    DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", roll);
}
