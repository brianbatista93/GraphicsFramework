#pragma once

using std::sqrt;

template<class T>
struct TVector3D
{
    union
    {
        T E[3];
        struct
        {
            T X;
            T Y;
            T Z;
        };
    };

    constexpr TVector3D()
      : X(0)
      , Y(0)
      , Z(0)
    {}

    constexpr TVector3D(T x, T y, T z)
      : X(x)
      , Y(y)
      , Z(z)
    {}

    constexpr TVector3D operator-() const { return TVector3D(-X, -Y, -Z); }

    constexpr T operator[](uint32 index) const { return E[index]; }

    constexpr T& operator[](uint32 index) { return E[index]; }

    template<class OtherType>
    constexpr TVector3D& operator+=(const TVector3D<OtherType>& other)
    {
        X += static_cast<T>(other.X);
        Y += static_cast<T>(other.Y);
        Z += static_cast<T>(other.Z);
        return *this;
    }

    template<class MultType, typename = std::enable_if_t<std::is_arithmetic_v<MultType>>>
    constexpr TVector3D& operator*=(const MultType other)
    {
        X *= static_cast<T>(other);
        Y *= static_cast<T>(other);
        Z *= static_cast<T>(other);
        return *this;
    }

    template<class MultType, typename = std::enable_if_t<std::is_arithmetic_v<MultType>>>
    constexpr TVector3D& operator/=(const MultType other)
    {
        return *this *= T(1) / static_cast<T>(other);
    }

    template<class OtherType>
    [[nodiscard]] constexpr T operator|(const TVector3D<OtherType>& other) const
    {
        return X * static_cast<T>(other.X) + Y * static_cast<T>(other.Y) + Z * static_cast<T>(other.Z);
    }

    template<class OtherType>
    [[nodiscard]] constexpr TVector3D operator^(const TVector3D<OtherType>& v) const
    {
        // clang-format off
        return TVector3D(E[1] * v.E[2] - E[2] * v.E[1],
                         E[2] * v.E[0] - E[0] * v.E[2],
                         E[0] * v.E[1] - E[1] * v.E[0]);
        // clang-format on
    }

    [[nodiscard]] constexpr T Length() const { return static_cast<T>(sqrt(*this | *this)); }

    [[nodiscard]] constexpr T LengthSquared() const { return X * X + Y * Y + Z * Z; }

    constexpr static TVector3D<T> Zero() { return TVector3D(0, 0, 0); }
    constexpr static TVector3D<T> One() { return TVector3D(1, 1, 1); }
    constexpr static TVector3D<T> Up() { return TVector3D(0, 1, 0); }
    constexpr static TVector3D<T> Down() { return -Up(); }
    constexpr static TVector3D<T> Forward() { return TVector3D(0, 0, 1); }
    constexpr static TVector3D<T> Backward() { return -Forward(); }
    constexpr static TVector3D<T> Right() { return TVector3D(1, 0, 0); }
    constexpr static TVector3D<T> Left() { return -Right(); }
};

template<class UType, class VType>
inline TVector3D<UType>
operator+(const TVector3D<UType>& u, const TVector3D<VType>& v)
{
    return TVector3D<UType>(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
}

template<class UType, class VType>
inline TVector3D<UType>
operator-(const TVector3D<UType>& u, const TVector3D<VType>& v)
{
    return TVector3D<UType>(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
}

template<class UType, class VType>
inline TVector3D<UType>
operator*(const TVector3D<UType>& u, const TVector3D<VType>& v)
{
    return TVector3D<UType>(u.X * v.X, u.Y * v.Y, u.Z * v.Z);
}

template<class SType, class UType>
inline TVector3D<UType>
operator*(SType s, const TVector3D<UType>& u)
{
    return TVector3D<UType>(u.X * UType(s), u.Y * UType(s), u.Z * UType(s));
}

template<class SType, class UType>
inline TVector3D<UType>
operator*(const TVector3D<UType>& u, SType s)
{
    return s * u;
}

template<class SType, class UType>
inline TVector3D<UType>
operator/(const TVector3D<UType>& u, SType s)
{
    return (SType(1) / s) * u;
}

template<class UType, class VType>
[[nodiscard]] inline UType
Dot(const TVector3D<UType>& u, const TVector3D<VType>& v)
{
    return u | v;
}

template<class UType, class VType>
[[nodiscard]] inline TVector3D<UType>
Cross(const TVector3D<UType>& u, const TVector3D<VType>& v)
{
    return u ^ v;
}

template<class UType>
[[nodiscard]] inline TVector3D<UType>
Normalize(const TVector3D<UType>& u)
{
    return u / u.Length();
}

using fVector3D = TVector3D<float>;
using dVector3D = TVector3D<double>;
using iVector3D = TVector3D<int32>;
using uVector3D = TVector3D<uint32>;

using Vector3D = fVector3D;