#include "PlayerCamera.h"
#include "Math.h"

PlayerCamera::PlayerCamera()
{
	Init();
}

void PlayerCamera::Init()
{
    pos = VGet(0, 20, 0);
    prePos = pos;
	dir = VGet(0.0f, 0.0f, 1.0f);
    acceleration = 10.0f;
    accel = InitAccel;
    velosity = InitVec;
	roll = 0.0f;
    pichi = yow = roll;
    radianInclement = ToRadian(30.0f);
	length = DefaultLength;

}

void PlayerCamera::Update(float deltaTime)
{
#if 0

    // 左右キーでカメラの回転値を変更
    if (CheckHitKey(KEY_INPUT_A))
    {
        roll -= radianInclement * deltaTime;
    }
    else if (CheckHitKey(KEY_INPUT_D))
    {
        roll += radianInclement * deltaTime;
    }
    // 値が大きくなりすぎないよう1周したら初期化する.
    if (roll > DX_PI_F * 2 || roll < DX_PI_F * -2)
    {
        roll = 0.0f;
    }

    VECTOR upDirection = VGet(sin(roll), cos(roll), 0.0f);
    upDirection = VNorm(upDirection);
    if (CheckHitKey(KEY_INPUT_W))
    {
        dir = VAdd(dir, VScale(upDirection, PichiUp * deltaTime));
    }
    else if (CheckHitKey(KEY_INPUT_S))
    {
        dir = VAdd(dir, VScale(upDirection, -PichiUp * deltaTime));

    }
    
    dir = VNorm(dir);
    velosity = VScale(dir, accel);
    prePos = VAdd(pos, VScale(velosity, deltaTime));
    pos = prePos;
    aimPos = VAdd(pos, VScale(dir, length));

   
    // 上方向は roll の値から算出
    SetCameraPositionAndTargetAndUpVec(pos, aimPos, upDirection);
#else
    
    //upDirectionがpicthi
    //upDirectionと(upDirectionと進行方向に垂直なベクトル)に垂直なベクトルがroll
    //upDirectionと進行方向に垂直なベクトルがyow
    // https://math.nakaken88.com/textbook/standard-inner-product-of-vector-and-perpendicular-vector/
    // chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://na-inet.jp/research/equation_cpp.pdf
    SetCameraPositionAndAngle(VGet(0.0f, 10.0f, 0.0f), dir.x, dir.y, dir.z);

#endif


}

void PlayerCamera::Input(float deltaTime)
{
}

void PlayerCamera::Draw()
{
    DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", roll);
}
