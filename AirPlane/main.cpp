#include "DxLib.h"
#include "DebugDraw.h"
#include "ObjectManager.h"


#include "PlayerCamera.h"
int WINAPI _stdcall WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	// �c�w���C�u��������������
	SetUseDirect3DVersion(DX_DIRECT3D_11);// �g�p����DirectX�o�[�W�������w��.

	// ��ʃ��[�h�Z�b�g.
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�̕ύX.
	SetGraphMode(1920, 1080, 16);
	SetBackgroundColor(70, 70, 70);

	SetDrawScreen(DX_SCREEN_BACK);// �`���𗠉�ʂɕύX����B

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���s0.01�`99999�܂ł��J�����̕`��͈͂Ƃ���B���ɗ��R�͂Ȃ��b�I.
	SetCameraNearFar(0.01f, 99999.0f);

	// ���C�g��ݒ�.
	SetLightDirection(VGet(0.0f, -1.0f, 0.0f));

	// �}�l�[�W���[����.
	ObjectManager::Initialize();

	PlayerCamera* camera = new PlayerCamera;
	ObjectManager::Entry(camera);

	//���Ԍv��.
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG prevTime = nowTime;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����Ԍv��.
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - prevTime) / 1000000.0f;
		ObjectManager::Update(deltaTime);

		ClearDrawScreen();
		ObjectManager::Draw();
		Debag::DrawGrid(30000, 10);
		ScreenFlip();
		prevTime = nowTime;
	}
	DxLib_End();

	return 0;
}