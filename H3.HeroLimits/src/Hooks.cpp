#include "Hooks.hpp"
#include "H3API.hpp"

#include "Localization.hpp"
#include "Config.hpp"
#include "Log.hpp"

#define MAX_HEROES 8
#define MAX_TOWNS 48
#define INVALID_HERO_ID 0xFFFFFFFF
#define INVALID_TOWN_ID 0xFFFFFFFF

Patcher* _P;
PatcherInstance* _PI;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
BYTE GetPlayerHeroes(h3::H3Player* player)
{
    BYTE hCount = 0;

    if (player)
    {
        for (BYTE i = 0; i < MAX_HEROES; i++)
        {
            hCount += player->heroIDs[i] != INVALID_HERO_ID;
        }

        for (BYTE i = 0; i < MAX_TOWNS; i++)
        {
            auto townId = player->towns[i];
            if (townId != INVALID_TOWN_ID)
            {
                for (auto& it : P_Main->towns)
                {
                    if (it.number == townId && it.owner == player->ownerID)
                    {
                        hCount += it.garrisonHero != INVALID_HERO_ID;
                    }
                }
            }
        }
    }

    return hCount;
}

/*
 *  There is no default checks for "if (town->buyHero())" so there is no way to safe exit function without buying hero
 * But only for human player. AI seems Ok with just fail buying.
 */
BOOL GetReturnAddressForBoughtFailure(_ptr_ orig, _ptr_& result)
{
    USHORT lookipSize = 64;    // exact offset is 0x22
    USHORT OPCODE_JE = 0x840F; // 0F 84 - je opcode,

    for (size_t i = 0; i < lookipSize; i++)
    {
        auto pOrig = reinterpret_cast<PUSHORT>(orig - i);

        if (*pOrig == OPCODE_JE)
        {
            result = reinterpret_cast<_ptr_>(pOrig);
            return TRUE;
        }
    }

    return FALSE;
}

BOOL IsHeroLimitReached(h3::H3Player* player)
{
    if (!player)
    {
        return FALSE;
    }

    switch (Config::Instance().Mode())
    {
    case Config::LimitationMode::Global:
        return GetPlayerHeroes(player) >= Config::Instance().HeroLimit();

    case Config::LimitationMode::Town:
        return GetPlayerHeroes(player) >= (player->townsCount * Config::Instance().HeroLimit());

    case Config::LimitationMode::None:
    default:
        return FALSE;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

_LHF_(TownBuyHero_LowLevel)
{
    auto pTown = reinterpret_cast<h3::H3Town*>(c->ecx);
    auto playerId = *reinterpret_cast<PUINT8>(c->esp + 8);

    if (playerId >= 8)
    {
        DEBUG_LOG("Player id invalid: %d", playerId);
        return EXEC_DEFAULT;
    }

    h3::H3Main* main = P_Main;
    h3::H3Player* player = &main->players[playerId];

    if (IsHeroLimitReached(player))
    {
        auto origRetAddress = *reinterpret_cast<_ptr_*>(c->esp);
        auto newRetAddress = origRetAddress;

        if (player->is_human)
        {
            auto text = Localization::Localize(LocalizationString::E_HERO_LIMIT_REACHED);
            h3::F_MessageBox(h3::H3String(text));

            if (GetReturnAddressForBoughtFailure(origRetAddress, newRetAddress))
            {
                // this needs to JE opcode jump worked
                // The flow with new ret address is just coming back to "close" tavern button
                c->flags.ZF = TRUE;
            }
        }

        c->return_address = newRetAddress;
        return NO_EXEC_DEFAULT;
    }

    DEBUG_LOG("Player id: %d. Buying hero.", playerId);
    return EXEC_DEFAULT;
}

void hooks_init(PatcherInstance* pi)
{
    pi->WriteLoHook(PLAYER_BUY_HERO, TownBuyHero_LowLevel);
}