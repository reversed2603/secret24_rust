#pragma once

#include "includes.hpp"
#include "../game/sdk.hpp"
#include "../utilities/returnspoofer.hpp"
#include "../utilities/memory.hpp"
#include "../features/menu/framework/gui_framework.h"

constexpr int max_hooks = 9;
inline std::array< uintptr_t, max_hooks > hook_address;