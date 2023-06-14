#pragma once
const int WindowMagnification = 100;
const int WindowX = 16 * WindowMagnification;
const int WindowY = 9 * WindowMagnification;
const int ColorBitNum = 16;
const float mouseSensitivity = 10.0f;

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
