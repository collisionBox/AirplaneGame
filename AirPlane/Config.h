#pragma once
const int WindowMagnification = 100;
const int WindowX = 16 * WindowMagnification;
const int WindowY = 9 * WindowMagnification;
const int ColorBitNum = 16;
const float mouseSensitivity = 10.0f;// マウス感度.
const float G = 9.80665f;// 重力加速度[m/s2].
const float GunTargetingDistance = 900.0f;// セカイン距離.

class Config
{
public:
	static void Initialize();
	static void Finalize();

private:
	Config();
	~Config();
	static Config* Instance;
	
};
