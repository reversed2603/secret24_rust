#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <vector>
#include <codecvt>
#include <algorithm>
#include <regex>
#include <memory>
#include <functional>
#include <stdio.h>
#include <Psapi.h>
#include <cstdint>
#include <chrono>
#include <array>
#include <inttypes.h>
#include <utility>
#include <coroutine>

#include "../utilities/math.hpp"
#include "../utilities/xor.hpp"

#include "../game/render/render.h"

#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "winmm.lib" )