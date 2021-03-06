#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hexagon/Core/Log.h"
#include "Hexagon/Debug/Instrumentor.h"

#ifdef HX_PLATFORM_WINDOWS
	#include <Windows.h>
#endif