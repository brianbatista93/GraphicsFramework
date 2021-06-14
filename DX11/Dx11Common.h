#pragma once

#include <d3d11.h>
#include <exception>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;

constexpr void
ThrowIfFailed(HRESULT result)
{
    if (FAILED(result)) {
        throw std::exception();
    }
}

#define SAFE_RELEASE(x)                                                                                                                    \
    if (x) {                                                                                                                               \
        x->Release();                                                                                                                      \
        x = nullptr;                                                                                                                       \
    }