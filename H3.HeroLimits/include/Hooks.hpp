#ifndef _HOOKS_HPP_
#define _HOOKS_HPP_

#define _FORCE_INLINE_
#define _H3_STD_CONVERSIONS_

#include "H3API.hpp"

#include "INIReader.h"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

void hooks_init(INIReader& reader, PatcherInstance* pi);

// function addresses
#define SHOW_TAVERN_DIALOG 0x5FF3A0
#define TOWN_BUY_HERO 0x5C16E0

#endif