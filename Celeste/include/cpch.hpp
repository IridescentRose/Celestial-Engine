/**
 * Precompiled Header for Celeste
 */
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
#include <chrono>
#include <iomanip>
#include <thread>

#include "Utilities/NonCopyable.hpp"
#include "Utilities/NonMovable.hpp"
#include "Utilities/Singleton.hpp"
#include "Utilities/ThreadSafe.hpp"
#include "Utilities/Types.hpp"
#include "Platform/Platform.h"
#include "Utilities/Timer.hpp"
#include "Utilities/Logger.hpp"
#include "Utilities/Profiler.hpp"

#if BUILD_PLAT == BUILD_POSIX
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#endif