#include "math/linear_algebra.h"
#include "tests/test_linear_algebra.h"
#include "util/log.h"

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

template <size_t N>
std::array<unsigned int, 2> test_vector() {
    std::vector<TestCase> tests = {
        { "default constructor"     , test_default_ctor<N>   },
        { "array constructor"       , test_arr_ctor<N>       },
        { "bracket accessor"        , test_bracket<N>        },
        { "xyzw accessor"           , test_accessor<N>       },
        { "equality"                , test_equality<N>       },
        { "inequality"              , test_inequality<N>     },
        { "addition"                , test_addition<N>       },
        { "subtraction"             , test_subtraction<N>    },
        { "multiplication"          , test_scalar_mult<N>    },
        { "division"                , test_scalar_div<N>     },
        { "component mult"          , test_component_mult<N> },
        { "component div"           , test_component_div<N>  },
        { "dot product"             , test_dot<N>            },
        { "distance"                , test_distance<N>       },
        { "linear interpolation"    , test_lerp<N>           }
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
