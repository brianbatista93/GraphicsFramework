#pragma once

#include "Vector3D.h"

struct Color
{
    union
    {
        float E[4];
        struct
        {
            float R;
            float G;
            float B;
            float A;
        };
    };

    Color()
      : R(0)
      , G(0)
      , B(0)
      , A(1)
    {}

    Color(float r, float g, float b, float a = 1.0)
      : R(r)
      , G(g)
      , B(b)
      , A(a)
    {}

    Color(const Vector3D& vec)
      : R(vec.X)
      , G(vec.Y)
      , B(vec.Z)
      , A(1.0f)
    {}
};

inline Color
operator*(float s, const Color& color)
{
    // clang-format off
    return Color(
        s * color.R,
        s * color.G,
        s * color.B
    );
    // clang-format on
}

inline Color
Lerp(const Color& a, const Color& b, float t)
{
    // clang-format off
    return Color((1.0f - t) * a.R + t * b.R, 
                 (1.0f - t) * a.G + t * b.G,
                 (1.0f - t) * a.B + t * b.B);
    // clang-format on
}