#pragma once

#include "INIReader.h"

#include <string>
#include <map>

#define NAME(x) #x
#define DELCARE_NAME(x) static constexpr auto x##_NAME = NAME(x);

/*
 *
 */
class LocalizationString
{
public:
	enum Type
	{
		E_HERO_LIMIT_REACHED = 0,
	};

public:

	template<typename T, typename ...Enums>
	class Names
	{
		static constexpr T Array[sizeof...(Enums)] =
		{
			&Enums...
		};
	};

	DELCARE_NAME(E_HERO_LIMIT_REACHED)
};


using LocalizationItem = LocalizationString::Type;
using Dictionary = std::map<LocalizationItem, std::string>;
using Language = std::string;

/*
 *
 */
class Localization
{
public:
	static void Initialize(INIReader& inifile);

	static std::string Localize(LocalizationItem string, ...);

	const Language& SystemLanguage() { return m_SystemLanguage; }

private:

	const Dictionary& GetDictionary(const Language& language = Language());

private:

	std::map<Language, Dictionary> m_Dictionaries{};

	Language m_SystemLanguage;
};


