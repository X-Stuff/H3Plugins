# H3 Hero limits plugin.

![windows-build](https://github.com/X-Stuff/H3Plugins/workflows/windows-build/badge.svg)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![Latest release](https://img.shields.io/github/v/release/x-stuff/h3plugins)](https://github.com/X-Stuff/H3Plugins/releases/latest)

## Overview

A plugin for **Heroes of Might and Magic III** game based on `H3API` library.  
*Version*: **0.0.1**

Required game version: `SOD`

Forked from: [`RoseKavalier's H3Plugins`](https://github.com/RoseKavalier/H3Plugins)

## Installation

1. Download `H3.HeroLimits.zip` archive from [latest release](https://github.com/X-Stuff/H3Plugins/releases/latest).
2. Extract Archive to `<HOMM3>/_HD3_Data/Packs/HeroLimits` folder.  
   > NOTE:  
   > You have to create `HeroLimits` folder (name could be any)
3. Configure plugin in `options.ini`.
4. Run `HDLauncher` and add `HeroLimits` plugin
5. Run game.

In case of error you will see a Message box.  
Unfortunately, right now, in case of success there will be no information.


## Functionality

1. Plugin allows to set additional hero limitation rules.
2. Limitation is only for hero buying. Prisononers not affected.
3. In case of town lost - nothing will happen to heroes count.
4. Harrison heroes **are counted** as well.

#### 1. Limitation Rules

##### Limitation values:
  Depending on mode means different:
  1. **Global** - maximum allowed heroes count for player. values from `8` and greater - ineffective. Game has own limitation for `8` heroes.
  2. **Per town** - maximum allowed heroes per player's town. for example:
     - player owns `1` town and `limitation value` is `2` - then maximum heroes count will be `1 * 2 = 2`
     - player owns `2` towns and `limitation value` is `3` - then maximum heroes count will be `2 * 3 = 6`

  Default limitation value is `1`

##### Modes:
  1. **Global** - Just maximum global limit per player.
  2. **Per town** - Player can buy a new hero in tavern only if hero count less than `Limiation value` multiplied on player's towns.
  3. **None** - Turns limitation off

  Default limitation value is **`Per town`**

#### 2. Configuration

Configuration is done via [`options.ini`](Resources/options.ini) file placed nearby plugin dll file.
Please see comments in the file for more details.

## Issues

Are welcome.

But since development is mostly assembler code debugging it will take a lot of time.

## Future

 * Limitation settings per scenario (map)
 * Limitation settings UI before scenario start
 * UI improvements
 * Network game support

But only if I will have time and passion for this.

#### Some info for developers:

 * Different default branch
 * Visual Studio 2019, toolset v142, Windows SDK 10+
 * Solution configured only for 2 projects: `H3.HeroLimits` and `H3API` (other projects are just for examples)
 * https://x64dbg.com/ as assembler debugger

-------
Copyright (c) 2020 Kaplin Dmitry ( https://t.me/dimitry_kaplin )