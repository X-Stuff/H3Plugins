#ifndef _HOOKS_HPP_
#define _HOOKS_HPP_

#define _H3API_PATCHER_X86_
#define _FORCE_INLINE_
#define _H3API_LIBRARY_
#define _H3_STD_CONVERSIONS_

#include "H3API.hpp"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

void hooks_init(PatcherInstance* pi);

#define E_HOTSEAT_TYPE 3

#define P_IsNetworkGame		DwordAt(0x69959C)
#define P_GameType			DwordAt(0x698A40)

#define PLAYER_SHOW_TAVERN_DIALOG 0x5FF3A0
#define PLAYER_BUY_HERO 0x5C16E0

#endif