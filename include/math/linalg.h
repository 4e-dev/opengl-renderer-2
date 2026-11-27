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
        ├─ dot                  [x]
        ├─ length / normalize   [x]
        ├─ distance             [x]
        ├─ lerp                 [x]
        ├─ cross                [ ]


    Mat3 ─┐
    Mat4 ─┼─ arithmetic
        ├─ matrix multiplication
        ├─ vector multiplication
        ├─ transpose
        ├─ determinant
        ├─ inverse
        ├─ cross

    Mat4 ── translation
        ├─ rotation
        ├─ scale
        ├─ perspective
        ├─ orthographic
        ├─ look_at

    Utilities
        ├─ radians / degrees
        ├─ clamp
        ├─ lerp
        ├─ transform_point/vector
*/

#include <array>
#include <cmath>
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

        // TODO: need to test these
        Vec& operator=(const Vec& other) { v = other; }
        Vec operator=(const Vec other) const { v = other; }

        double x() const { return v[0]; }
        double y() const requires (N >= 2) { return v[1]; }
        double z() const requires (N >= 3) { return v[2]; }
        double w() const requires (N >= 4) { return v[3]; }

        const static size_t dim = N;
};

using Vec2 = Vec<2>();
using Vec3 = Vec<3>();
using Vec4 = Vec<4>();

template <size_t N>
std::ostream& operator<<(std::ostream& stream, const Vec<N>& vec)
{
    // always show some fixed number of decimal points
    stream << std::fixed << std::setprecision(2);
    stream << "Vec<" << N << ">{ ";
    for (size_t i{0}; i < vec.size(); ++i)
    {
        double val = vec[i];
        if (i > 0) {
            stream << ", ";
        }
        stream << val;
    }
    stream << " }";
    return stream;
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

template <size_t N>
Mat<N, N> identity() {
    Mat<N, N> mat{};
    for (auto i : std::views::iota(0uz, N)) {
        mat[i][i] = 1.0;
    }
    return mat;
}

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

template<size_t Rows, size_t Cols>
bool operator==(const Mat<Rows, Cols>& lhs, const Mat<Rows, Cols>& rhs) {
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template<size_t Rows, size_t Cols>
bool operator!=(const Mat<Rows, Cols>& lhs, const Mat<Rows, Cols>& rhs) {
    return !(lhs == rhs);
}

// NOTE: matrices must be equal dimension for addition and subtraction operations
template<size_t Rows, size_t Cols>
Mat<Rows, Cols> operator+(const Mat<Rows, Cols>& lhs, const Mat<Rows, Cols>& rhs) {
    Mat<Rows, Cols> result{};

    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            result[i][j] = lhs[i][j] + rhs[i][j];
        }
    }

    return result;
}

template<size_t Rows, size_t Cols>
void operator+=(Mat<Rows, Cols>& lhs, const Mat<Rows, Cols>& rhs) {
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            lhs[i][j] += rhs[i][j];
        }
    }
}

template<size_t Rows, size_t Cols>
Mat<Rows, Cols> operator-(const Mat<Rows, Cols>& lhs, const Mat<Rows, Cols>& rhs) {
    Mat<Rows, Cols> result{};

    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            result[i][j] = lhs[i][j] - rhs[i][j];
        }
    }

    return result;
}

template<size_t Rows, size_t Cols>
void operator-=(Mat<Rows, Cols>& lhs, const Mat<Rows, Cols>& rhs) {
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            lhs[i][j] -= rhs[i][j];
        }
    }
}

template<size_t Rows, size_t Cols>
Mat<Rows, Cols> operator*(const Mat<Rows, Cols>& mat, const double scalar) {
    Mat<Rows, Cols> scaled{};
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            scaled[i][j] = mat[i][j] * scalar;
        }
    }
    return scaled;
}

template<size_t Rows, size_t Cols>
Mat<Rows, Cols> operator*(const double scalar, const Mat<Rows, Cols>& mat) {
    return mat * scalar;
}

template<size_t Rows, size_t Cols>
void operator*=(Mat<Rows, Cols>& mat, const double scalar) {
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            mat[i][j] *= scalar;
        }
    }
}

template<size_t Rows, size_t Cols>
Mat<Rows, Cols> operator/(const Mat<Rows, Cols>& mat, const double scalar) {
    Mat<Rows, Cols> scaled{};
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            scaled[i][j] = mat[i][j] / scalar;
        }
    }
    return scaled;
}

template<size_t Rows, size_t Cols>
void operator/=(Mat<Rows, Cols>& mat, const double scalar) {
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            mat[i][j] /= scalar;
        }
    }
}

// matrix multiplication
template<size_t Rows, size_t Inner, size_t Cols>
Mat<Rows, Cols> operator*(
    const Mat<Rows, Inner>& lhs,
    const Mat<Inner, Cols>& rhs) {

    /*
       Implementing this was trickier than I thought.
       It's helpful to think of indices `i` and `j` as the current 'destination' cells.
       `k` is used to match the correct pair of elements.
        */

    Mat<Rows, Cols> result{};

    // First two loops for destination of `result`
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            // Third loop for calculating result[i][j]
            double sum{0.0};
            for (auto k : std::views::iota(0uz, Inner)) {
                sum += lhs[i][k] * rhs[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

// TODO: NEEDS TEST
template<size_t Rows, size_t Cols>
Vec<Rows> operator*(const Mat<Rows, Cols>& mat, const Vec<Cols>& vec) {
    Vec<Rows> result{};
    for (auto i : std::views::iota(0uz, Rows)) {
        for (auto j : std::views::iota(0uz, Cols)) {
            result[i] += mat[i][j] * vec[j];
        }
    }
    return result;
}

// TODO: NEEDS TEST
template<size_t Rows, size_t Cols>
Vec<Cols> operator*(const Vec<Rows>& vec, const Mat<Rows, Cols>& mat) {
    Vec<Cols> result{};
    for (auto i : std::views::iota(0uz, Cols)) {
        for (auto j : std::views::iota(0uz, Rows)) {
            result[i] += mat[j][i] * vec[j];
        }
    }
    return result;
}
