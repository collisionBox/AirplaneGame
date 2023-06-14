#include "Config.h"


Config* Config::Instance = nullptr;
Config::Config()
{
	Instance = nullptr;
}

Config::~Config()
{
	Instance = nullptr;
}

void Config::Initialize()
{
	if (!Instance)
	{
		Instance = new Config;
	}

}

void Config::Finalize()
{
	if (Instance)
	{
		delete Instance;
	}
}
