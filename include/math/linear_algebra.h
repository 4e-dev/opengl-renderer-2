/*
   Header-only, custom linear algebra library
   */

#pragma once

/* NOTE: removing inline can be useful for debugging compiler behavior / benchmarking
   or just letting the compiler do its thang.
   */

#ifdef DO_NOT_DECLARE_INLINE
#define STATIC_INLINE static
#else
#define STATIC_INLINE static inline
#endif

/*
   Version 1.0 targets to implement.

    Vec2 ─┐
    Vec3 ─┼─ arithmetic (add, subtract, multiply, divide) [x]
    Vec4 ─┘
        ├─ dot [x]
        ├─ length / normalize [x]
        ├─ distance [x]
        ├─ lerp [x]


    (cross (Vec3), whwich is basically a 3x1 matrix)
    Mat3 ─┐
    Mat4 ─┼─ arithmetic
        ├─ matrix multiplication
        ├─ vector multiplication
        ├─ transpose
        ├─ determinant
        └─ inverse

    Mat4 ── translation
        ── rotation
        ── scale
        ── perspective
        ── orthographic
        └── look_at

    Utilities
        ├── radians / degrees
        ├── clamp
        ├── lerp
        └── transform_point/vector
*/

#include <array>
#include <cmath>

template <size_t N>
requires (N >= 1)
class Vec {
private:
    std::array<double, N> v{};

public:
    Vec() = default;

    Vec(const std::array<double, N> values)
        : v(values) {}

    double operator[](const size_t i) const {
        return v[i];
    }

    double& operator[](const size_t i) {
        return v[i];
    }

    double x() const { return v[0]; }
    double y() const requires (N >= 2) { return v[1]; }
    double z() const requires (N >= 3) { return v[2]; }
    double w() const requires (N >= 4) { return v[3]; }

    static constexpr size_t dim = N;
};

template <size_t N>
bool operator==(const Vec<N>& lhs, const Vec<N>& rhs) {
    for (size_t i{0}; i < N; ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template <size_t N>
bool operator!=(const Vec<N>& lhs, const Vec<N>& rhs) {
    return !(lhs == rhs);
}

template <size_t N>
Vec<N> operator+(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i)
        a[i] = lhs[i] + rhs[i];
    return Vec<N>(a);
}

template <size_t N>
void operator+=(Vec<N>& lhs, const Vec<N>& rhs) {
    for (size_t i{0}; i < N; ++i)
        lhs[i] += rhs[i];
}

template <size_t N>
Vec<N> operator-(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i)
        a[i] = lhs[i] - rhs[i];
    return Vec<N>(a);
}

template <size_t N>
void operator-=(Vec<N>& lhs, Vec<N>& rhs) {
    for (size_t i{0}; i < N; ++i)
        lhs[i] -= rhs[i];
}

template <size_t N>
Vec<N> operator*(const Vec<N>& v, const double scalar) {
    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i) {
        a[i] = v[i] * scalar;
    }
    return Vec<N>(a);
}

template <size_t N>
Vec<N> operator*(const double scalar, const Vec<N>& v) {
    return v * scalar;
}

template<size_t N>
Vec<N> operator*=(Vec<N>& v, const double scalar) {
    for (size_t i{0}; i < N; ++i)
        v[i] *= scalar;
}

template<size_t N>
Vec<N> operator/(const Vec<N>& v, const double scalar) {
    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i) {
        a[i] = v[i] / scalar;
    }
    return Vec<N>(a);
}

template<size_t N>
Vec<N> component_multiply(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i)
        a[i] = lhs[i] * rhs[i];
    return Vec<N>(a);
}

template<size_t N>
Vec<N> component_divide(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i)
        a[i] = lhs[i] / rhs[i];
    return Vec<N>(a);
}

template <typename VecType>
STATIC_INLINE double dot(const VecType& lhs, const VecType& rhs) {
    double result {0.0};
    for (size_t i{0}; i < VecType::dim; ++i)
        result += (lhs[i] * rhs[i]);
    return result;
}

template <typename VecType>
STATIC_INLINE double distance(const VecType& u, const VecType& v) {
    double d{0.0};
    for (size_t i{0}; i < VecType::dim; ++i) {
        d += pow((u[i] - v[i]), 2);
    }
    d = sqrt(d);
    return d;
}

STATIC_INLINE double lerp(
    const double start,
    const double end,
    const double factor) {
    return start + (end - start) * factor;
}

template <typename VecType>
STATIC_INLINE VecType lerp(
    const VecType& start,
    const VecType& end,
    const double factor) {
    const size_t N {VecType::dim};

    std::array<double, N> a{};
    for (size_t i{0}; i < N; ++i) {
        a[i] = lerp(start[i], end[i], factor);
    }
    return VecType(a);
}
