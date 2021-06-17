#pragma once

#include <cmath>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using int8  = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

#define HAS_FLAG(bits, flag) (bits & flag) == flag

#define BIT(x) 1 << x

#define SAFE_DELETE(x)                                                                                                                     \
    if (x) {                                                                                                                               \
        delete x;                                                                                                                          \
        x = nullptr;                                                                                                                       \
    }

#define SAFE_DELETE_ARRAY(x)                                                                                                               \
    if (x) {                                                                                                                               \
        delete[] x;                                                                                                                        \
        x = nullptr;                                                                                                                       \
    }

#if _WIN32
    #include <DirectXMath.h>

using namespace DirectX;
#endif // WIN32