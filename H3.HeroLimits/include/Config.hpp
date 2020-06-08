#pragma once

#include "INIReader.h"

class Config
{
public:
	enum class LimitationMode
	{
		None = 0,

		Town,

		Global
	};

public:

	static void Initialize(INIReader& inifile);

	static const Config& Instance() { return s_Instance; }

	LimitationMode Mode() const { return m_Mode; }

	uint8_t HeroLimit() const { return m_HeroLimit; }

private:

	static Config s_Instance;

	LimitationMode m_Mode{ LimitationMode::Town };

	uint8_t m_HeroLimit{ 0 };
};