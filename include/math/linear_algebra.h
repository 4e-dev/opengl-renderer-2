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
#include <exception>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

template <size_t N>
requires (N >= 1)
class Vec {
    private:
        std::array<double, N> v{};

    public:
        Vec() = default;

        Vec(const std::array<double, N> values) : v(values) {}

        double operator[](const size_t i) const { return v[i]; }
        double& operator[](const size_t i) { return v[i]; }

        // TODO: test these
        Vec& operator=(const Vec& other) { v = other; }
        Vec operator=(const Vec other) const { v = other; }

        auto begin() { return v.begin(); }
        auto begin() const { return v.begin(); }

        auto end() { return v.end(); }
        auto end() const { return v.end(); }

        double x() const { return v[0]; }
        double y() const requires (N >= 2) { return v[1]; }
        double z() const requires (N >= 3) { return v[2]; }
        double w() const requires (N >= 4) { return v[3]; }

        static constexpr size_t dim = N;
}; // Vec

template <size_t N>
std::ostream& operator<<(std::ostream& os, const Vec<N>& v) {
    // always show some decimal points
    os << std::fixed << std::setprecision(2);
    os << "Vec<" << N << ">{ ";
    size_t i{0};
    for (const double val : v) {
        if (i > 0) {
            os << ", ";
        }
        os << val;
        ++i;
    }
    os << " }";
    return os;
}

template <size_t N>
bool operator==(const Vec<N>& lhs, const Vec<N>& rhs) {
    for (auto i : std::views::iota(0uz, N)) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <size_t N>
bool operator!=(const Vec<N>& lhs, const Vec<N>& rhs) {
    return !(lhs == rhs);
}

template <size_t N>
Vec<N> operator+(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
        a[i] = lhs[i] + rhs[i];
    }
    return Vec<N>(a);
}

template <size_t N>
void operator+=(Vec<N>& lhs, const Vec<N>& rhs) {
    for (auto i : std::views::iota(0uz, N)) {
        lhs[i] += rhs[i];
    }
}

template <size_t N>
Vec<N> operator-(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
        a[i] = lhs[i] - rhs[i];
    }
    return Vec<N>(a);
}

template <size_t N>
void operator-=(Vec<N>& lhs, Vec<N>& rhs) {
    for (auto i : std::views::iota(0uz, N)) {
        lhs[i] -= rhs[i];
    }
}

template <size_t N>
Vec<N> operator*(const Vec<N>& v, const double scalar) {
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
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
    for (auto i : std::views::iota(0uz, N)) {
        v[i] *= scalar;
    }
}

template<size_t N>
Vec<N> operator/(const Vec<N>& v, const double scalar) {
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
        a[i] = v[i] / scalar;
    }
    return Vec<N>(a);
}

template<size_t N>
Vec<N> component_multiply(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
        a[i] = lhs[i] * rhs[i];
    }
    return Vec<N>(a);
}

template<size_t N>
Vec<N> component_divide(const Vec<N>& lhs, const Vec<N>& rhs) {
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
        a[i] = lhs[i] / rhs[i];
    }
    return Vec<N>(a);
}

template <typename VecType>
STATIC_INLINE double dot(const VecType& lhs, const VecType& rhs) {
    double result {0.0};
    for (auto i : std::views::iota(0uz, VecType::dim)) {
        result += (lhs[i] * rhs[i]);
    }
    return result;
}

template <typename VecType>
STATIC_INLINE double distance(const VecType& u, const VecType& v) {
    double d{0.0};
    for (auto i : std::views::iota(0uz, VecType::dim)) {
        d += pow((u[i] - v[i]), 2);
    }
    return sqrt(d);
}

STATIC_INLINE double lerp(const double start, const double end, const double factor) {
    return start + (end - start) * factor;
}

template <typename VecType>
STATIC_INLINE VecType lerp(const VecType& start, const VecType& end, const double factor) {
    const size_t N {VecType::dim};
    std::array<double, N> a{};
    for (auto i : std::views::iota(0uz, N)) {
        a[i] = lerp(start[i], end[i], factor);
    }
    return VecType(a);
}

// --------------------------------------------
// TODO: working on matrix and matrix operators
// --------------------------------------------

template <size_t Rows, size_t Cols>
requires (Rows >= 1 && Cols >= 1)
class Mat {
    private:
        //std::array<std::array<double, Cols>, Rows> data;
        std::vector<std::vector<double>> data;

    public:
        Mat() {
            data.resize(Rows, std::vector<double>(Cols, 0.0));
        }

        Mat(const std::vector<std::vector<double>>& values) {
            size_t rows = values.size();
            size_t cols = values[0].size();

            if (rows != Rows || cols != Cols) {
                std::string message{};
                message += "\nInitializer list is of incorrect size!\n";
                message += std::format("Expected <{}, {}>\n", Rows, Cols);
                message += std::format("Given <{}, {}>\n", rows, cols);
                throw std::invalid_argument(message);
            }
            data = values;
        }

        auto& operator[](const size_t i) { return data[i]; }
        const auto& operator[](const size_t i) const { return data[i]; }

        static constexpr size_t nrows = Rows;
        static constexpr size_t ncols = Cols;
}; // Mat

template <size_t Rows, size_t Cols>
std::ostream& operator<<(std::ostream& os, const Mat<Rows, Cols>& matrix) {
    // always show some decimal points
    os << std::fixed << std::setprecision(2);

    os << "Mat<" << Rows << ", " << Cols << "> = \n";

    for (auto i : std::views::iota(0uz, Rows)) {
        std::pair<std::string, std::string> brackets{};

        if (i == 0)
            brackets = {"⎡", "⎤"};
        else if (i == Rows-1)
            brackets = {"⎣", "⎦"};
        else
            brackets = {"⎢", "⎢"};

        os << brackets.first << " ";
        for (auto j : std::views::iota(0uz, Cols)) {
            os << matrix[i][j] << " ";
        }
        os << brackets.second << '\n';
    }

    return os;
}
