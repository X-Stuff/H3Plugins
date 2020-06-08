#include "Config.hpp"

Config Config::s_Instance;

void Config::Initialize(INIReader& inifile)
{
	s_Instance.m_Mode = (LimitationMode)
		inifile.GetInteger("settings", "LimitationMode", (int)LimitationMode::Town);

	s_Instance.m_HeroLimit = (uint8_t)inifile.GetInteger("settings", "MaximumHeroes", 1);
}
