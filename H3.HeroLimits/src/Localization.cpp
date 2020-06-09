#include "Localization.hpp"

#include <stdarg.h>
#include <locale>

Localization s_Singleton;
Dictionary s_Default =
{
    std::make_pair(LocalizationString::E_HERO_LIMIT_REACHED, "Can't buy another hero! Limit reached.")
};

/*
 * TODO: This doesn't work. Need to get default system language in some other way
 */
Language GetSystemLanguage()
{
    auto locale = std::locale("").name();
    if (locale.length() > 0)
    {
        auto lang = locale.substr(0, 2);
        for (size_t i = 0; i < lang.length(); i++)
        {
            lang[i] = ::toupper(lang[i]);
        }

        return lang;
    }

    return Language();
}


Dictionary ReadDictionary(INIReader& inifile, std::string section)
{
    static const std::string empty;
    Dictionary dict;

    for (auto i = LocalizationItem::FIRST + 1; i < LocalizationItem::LAST; ++i)
    {
        auto result = inifile.Get(section, LocalizationString::ToString(i), empty);
        if (result != empty)
        {
            dict[i] = result;
        }
    }

    return dict;
}

void Localization::Initialize(INIReader& inifile)
{
    s_Singleton.m_SystemLanguage = inifile.Get("Localization", "Language", GetSystemLanguage());

    s_Singleton.m_Dictionaries.clear();
    s_Singleton.m_Dictionaries[std::string()] = s_Default;

    auto sections = inifile.Get("Localization", "AvailableDictionaries", "");
    if (sections.length() > 0)
    {
        size_t start = 0;
        auto length = sections.length();

        while (start < length)
        {
            auto end = sections.find(',', start);
            auto culture = sections.substr(start, end - start);
            start += culture.length() + 1;

            if (culture.length() > 0)
            {
                auto dictSection = "Localization_" + culture;
                auto sections = inifile.Sections(); // copy creates here

                if (sections.find(dictSection) != sections.end())
                {
                    s_Singleton.m_Dictionaries[culture] = ReadDictionary(inifile, dictSection);
                }
            }
        }
    }
}

std::string Localization::Localize(LocalizationItem string, ...)
{
    Language lookup[2] =
    {
        s_Singleton.SystemLanguage(),
        Language()
    };

    for (size_t i = 0; i < sizeof(lookup); i++)
    {
        auto& dictionary = s_Singleton.GetDictionary(lookup[i]);

        auto& found = dictionary.find(string);
        if (found != dictionary.end())
        {
            va_list va;
            va_start(va, string);

            static char buffer[1024 * 8]{ 0 };
            vsprintf_s(buffer, sizeof(buffer), found->second.c_str(), va);

            va_end(va);

            return std::string(buffer);
        }
    }

    return std::string();
}

const Dictionary& Localization::GetDictionary(const Language& language)
{
    auto& found = m_Dictionaries.find(language);

    return found == m_Dictionaries.end() ? s_Default : found->second;
}
