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

    Color& operator+=(const Color& other)
    {
        R += other.R;
        G += other.G;
        B += other.B;
        return *this;
    }
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
operator*(const Color& a, const Color& b)
{
    // clang-format off
    return Color(
        a.R * b.R,
        a.G * b.G,
        a.B * b.B
    );
    // clang-format on
}

inline Color
operator+(const Color& a, const Color& b)
{
    // clang-format off
    return Color(
        a.R + b.R,
        a.G + b.G,
        a.B + b.B
    );
    // clang-format on
}

template<class SType, typename = std::enable_if_t<std::is_arithmetic_v<SType>>>
inline Color
operator/(const Color& color, SType s)
{
    float t = 1.0f / static_cast<float>(s);
    // clang-format off
    return Color(
        color.R * t,
        color.G * t,
        color.B * t
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