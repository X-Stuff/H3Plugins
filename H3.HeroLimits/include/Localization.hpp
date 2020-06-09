#pragma once

#include "INIReader.h"

#include <string>
#include <map>

#include "Utils.hpp"

DECLARE_ENUM_CLASS(LocalizationString,
    E_HERO_LIMIT_REACHED);


using LocalizationItem = LocalizationString::Values;
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


