#include "tests/test_linear_algebra.h"

using Test = bool(*)();
struct TestCase {
    std::string description;
    Test run;
};

// random number generator
std::random_device random_device{};
std::mt19937 gen(random_device());
std::uniform_real_distribution<double> distrib(1.0, 100.0);

// -----------------------------

namespace TVec {
template <size_t N>
bool test_default_ctor() {
    Vec<N> v{};
    for (size_t i{0}; i < N; ++i)
        if (v[i] != 0.0)
            return false;
    return true;
}

template <size_t N>
bool test_arr_ctor() {
    std::array<double, N> a;
    for (size_t i{0}; i < N; ++i)
        a[i] = distrib(gen);
    Vec<N> v(a);
    for (size_t i{0}; i < N; ++i)
        if (v[i] != a[i])
            return false;
    return true;
}

template <size_t N>
bool test_bracket() {
    // fill with random numbers
    std::array<double, N> a;
    for (size_t i{0}; i < N; ++i)
        a[i] = distrib(gen);

    Vec<N> v(a);
    for (size_t i{0}; i < N; ++i)
        if (v[i] != a[i])
            return false;
    return true;
}

template <size_t N>
bool test_accessor() {
    // fill with random numbers
    std::array<double, N> a;
    for (size_t i{0}; i < N; ++i)
        a[i] = distrib(gen);

    Vec<N> v(a);

    bool x = true;
    bool y = true;
    bool z = true;
    bool w = true;

    x = v.x() == a[0];
    if constexpr (N >= 2) y = v.y() == a[1];
    if constexpr (N >= 3) z = v.z() == a[2];
    if constexpr (N >= 4) w = v.w() == a[3];

    return x && y && z && w;
}

template <size_t N>
bool test_equality() {
    // fill with random numbers
    std::array<double, N> a;
    for (size_t i{0}; i < N; ++i)
        a[i] = distrib(gen);

    Vec<N> v1(a), v2(a);
    return v1 == v2;
}

template <size_t N>
bool test_inequality() {
    Vec<N> v1{}, v2{};
    for (size_t i{0}; i < N; ++i) {
        v1[i] = static_cast<double>(i);
        v2[i] = static_cast<double>(i*2);
    }
    return v1 != v2;
}

template <size_t N>
bool test_addition() {
    std::array<double, N> a1{}, a2{}, a3{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = distrib(gen);
        a3[i] = a1[i] + a2[i];
    }

    Vec<N> v1(a1), v2(a2), v3(a3);
    return v1 + v2 == v3;
}

template <size_t N>
bool test_subtraction() {
    std::array<double, N> a1{}, a2{}, a3{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = distrib(gen);
        a3[i] = a1[i] - a2[i];
    }

    Vec<N> v1(a1), v2(a2), v3(a3);
    return v1 - v2 == v3;
}

template <size_t N>
bool test_scalar_mult() {
    const double scalar = distrib(gen);
    std::array<double, N> a1{}, a2{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = a1[i] * scalar;
    }

    Vec<N> v1(a1), v2(a2);
    return (v1 * scalar == v2) && (scalar * v1 == v2);
}

template <size_t N>
bool test_scalar_div() {
    const double scalar = distrib(gen);
    std::array<double, N> a1{}, a2{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = a1[i] / scalar;
    }
    Vec<N> v1(a1), v2(a2);
    return v1 / scalar == v2;
}

template <size_t N>
bool test_component_mult() {
    std::array<double, N> a1{}, a2{}, a3{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = distrib(gen);
        a3[i] = a1[i] * a2[i];
    }
    Vec<N> v1(a1), v2(a2), v3(a3);
    return component_multiply(v1, v2) == v3;
}

template <size_t N>
bool test_component_div() {
    std::array<double, N> a1{}, a2{}, a3{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = distrib(gen);
        a3[i] = a1[i] / a2[i];
    }
    Vec<N> v1(a1), v2(a2), v3(a3);
    return component_divide(v1, v2) == v3;
}

template <size_t N>
bool test_dot() {
    std::array<double, N> a1{}, a2{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = distrib(gen);
        a2[i] = distrib(gen);
    }

    Vec<N> v1(a1), v2(a2);
    double expected{};
    for (size_t i{0}; i < N; ++i) {
        expected += a1[i] * a2[i];
    }
    return dot(v1, v2) == expected;
}

template <size_t N>
bool test_distance() {
    std::array<double, N> a1{}, a2{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = static_cast<double>(i);
        a2[i] = static_cast<double>(i + 1);
    }
    Vec<N> v1(a1), v2(a2);
    return distance(v1, v2) == std::sqrt(static_cast<double>(N));
}

template <size_t N>
bool test_lerp() {
    std::array<double, N> a1{}, a2{};
    for (size_t i{0}; i < N; ++i) {
        a1[i] = static_cast<double>(i);
        a2[i] = static_cast<double>(i + 2);
    }

    Vec<N> v1(a1), v2(a2);
    Vec<N> result = lerp(v1, v2, 0.5);

    for (size_t i{0}; i < N; ++i) {
        double expected {(a1[i] + a2[i]) / 2.0};
        if (result[i] != expected)
            return false;
    }
    return true;
}
}; // TVec

template <size_t N>
std::array<unsigned int, 2> test_vector() {
    /*
       returns the number tests and the number of tests *failed*
    */

    std::vector<TestCase> tests = {
        { "default constructor"     , TVec::test_default_ctor<N>   },
        { "array constructor"       , TVec::test_arr_ctor<N>       },
        { "bracket accessor"        , TVec::test_bracket<N>        },
        { "xyzw accessor"           , TVec::test_accessor<N>       },
        { "equality"                , TVec::test_equality<N>       },
        { "inequality"              , TVec::test_inequality<N>     },
        { "addition"                , TVec::test_addition<N>       },
        { "subtraction"             , TVec::test_subtraction<N>    },
        { "multiplication"          , TVec::test_scalar_mult<N>    },
        { "division"                , TVec::test_scalar_div<N>     },
        { "component mult"          , TVec::test_component_mult<N> },
        { "component div"           , TVec::test_component_div<N>  },
        { "dot product"             , TVec::test_dot<N>            },
        { "distance"                , TVec::test_distance<N>       },
        { "linear interpolation"    , TVec::test_lerp<N>           }
    };

    unsigned int tests_failed{0};
    for (const auto& test : tests) {
        if (!test.run()) {
            ++tests_failed;
            std::string message = std::format("TEST FAILED: {}", test.description);
            log(message, FAIL);
        }
    }
    return {static_cast<unsigned int>(tests.size()), tests_failed};
}

// explicit instantiation (for testing)
template std::array<unsigned int, 2> test_vector<2>();
template std::array<unsigned int, 2> test_vector<3>();
template std::array<unsigned int, 2> test_vector<4>();

namespace TMat {
    template<size_t Rows, size_t Cols>
    bool test_default_ctor() {
        Mat<Rows, Cols> mat{};
        for (auto i : std::views::iota(0uz, Rows)) {
            for (auto j : std::views::iota(0uz, Cols)) {
                if (mat[i][j] != 0.0) {
                    return false;
                }
            }
        }
        return true;
    }

    template<size_t Rows, size_t Cols>
    bool test_init_list_ctor() {
        std::vector<std::vector<double>> initializer{};
        initializer.reserve(Rows);

        // generate random values for initializer
        for (auto _ : std::views::iota(0uz, Rows)) {
            std::vector<double> line{};
            line.reserve(Cols);
            for (auto _ : std::views::iota(0uz, Cols)) {
                line.emplace_back(distrib(gen));
            }
            initializer.emplace_back(line);
        }

        // construct
        Mat<Rows, Cols> mat{initializer};

        // compare init list with matrix
        for (auto i : std::views::iota(0uz, Rows)) {
            for (auto j : std::views::iota(0uz, Cols)) {
                if (mat[i][j] != initializer[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    //bool test_bracket
    //bool test_accessor
    //bool test_equality
    //bool test_inequality
    //bool test_addition
    //bool test_subtraction
    //bool test_scalar_mult
    //bool test_scalar_div
    //bool test_component_mult
    //bool test_component_div
    //bool test_dot
    //bool test_distance
    //bool test_lerp
}; // TMat

template <size_t Rows, size_t Cols>
std::array<unsigned int, 2> test_matrix() {
    std::vector<TestCase> tests = {
        {"default constructor", TMat::test_default_ctor<Rows, Cols>},
        {"initializer list constructor", TMat::test_init_list_ctor<Rows, Cols>}
    };

    unsigned int tests_failed{0};
    for (const auto& test : tests) {
        if (!test.run()) {
            ++tests_failed;
            std::string message = std::format("TEST FAILED: {}", test.description);
            log(message, FAIL);
        }
    }
    return {static_cast<unsigned int>(tests.size()), tests_failed};
}

// explicit instantiation (for testing)
template std::array<unsigned int, 2> test_matrix<3, 3>();
template std::array<unsigned int, 2> test_matrix<4, 4>();
