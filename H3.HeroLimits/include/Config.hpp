#pragma once

#include "INIReader.h"

/*
 * Global configuration for plugin
 */
class Config
{
public:
    enum class LimitationMode
    {
        /*
         * No limitation rules will be applied
         */
        None = 0,

        /*
         * Limit hero count per town
         */
        Town,

        /*
         * Limit global hero count for every player
         */
        Global
    };

public:

    /*
     * Initialize configuration signleton object from settings from ini file
     */
    static void Initialize(INIReader& inifile);

    /*
     * Configuration singleton object
     */
    static const Config& Instance() { return s_Instance; }

    /*
     * Current limitation mode
     */
    LimitationMode Mode() const { return m_Mode; }

    /*
     * Current limit value
     */
    uint8_t HeroLimit() const { return m_HeroLimit; }

private:

    static Config s_Instance;

    LimitationMode m_Mode{ LimitationMode::Town };

    uint8_t m_HeroLimit{ 0 };
};