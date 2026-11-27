#include "test_linalg.h"

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
}; // namespace TVec

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

    template <size_t Rows, size_t Cols>
        bool test_equality() {
            Mat<Rows, Cols> lhs{}, rhs{};
            for (auto i : std::views::iota(0uz, Rows)) {
                for (auto j : std::views::iota(0uz, Cols)) {
                    lhs[i][j] = distrib(gen);
                    rhs[i][j] = lhs[i][j];
                }
            }
            return lhs == rhs;
        }

    template <size_t Rows, size_t Cols>
        bool test_inequality() {
            Mat<Rows, Cols> lhs{}, rhs{};
            for (auto i : std::views::iota(0uz, Rows)) {
                for (auto j : std::views::iota(0uz, Cols)) {
                    lhs[i][j] = distrib(gen);
                    rhs[i][j] = lhs[i][j] * 2.0;
                }
            }
            return lhs != rhs;
        }

    template <size_t Rows, size_t Cols>
        bool test_addition() {
            Mat<Rows, Cols> lhs{}, rhs{}, expected{};
            for (auto i : std::views::iota(0uz, Rows)) {
                for (auto j : std::views::iota(0uz, Cols)) {
                    lhs[i][j] = distrib(gen);
                    rhs[i][j] = distrib(gen);
                    expected[i][j] = lhs[i][j] + rhs[i][j];
                }
            }

            // regular addition
            if (lhs + rhs != expected) {
                return false;
            }

            // compound assignment operator
            lhs += rhs;
            return lhs == expected;
        }

    template <size_t Rows, size_t Cols>
        bool test_subtraction() {
            Mat<Rows, Cols> lhs{}, rhs{}, expected{};
            for (auto i : std::views::iota(0uz, Rows)) {
                for (auto j : std::views::iota(0uz, Cols)) {
                    lhs[i][j] = distrib(gen);
                    rhs[i][j] = distrib(gen);
                    expected[i][j] = lhs[i][j] - rhs[i][j];
                }
            }

            // regular subtraction
            if (lhs - rhs != expected) {
                return false;
            }

            // compound assignment operator
            lhs -= rhs;
            return lhs == expected;
        }

    template <size_t Rows, size_t Cols>
        bool test_scalar_mult() {
            Mat<Rows, Cols> mat{}, expected{};
            double scalar{distrib(gen)};

            for (auto i : std::views::iota(0uz, Rows)) {
                for (auto j : std::views::iota(0uz, Cols)) {
                    mat[i][j] = distrib(gen);
                    expected[i][j] = mat[i][j] * scalar;
                }
            }

            return mat * scalar == expected;
        }

    template <size_t Rows, size_t Cols>
        bool test_scalar_div() {
            Mat<Rows, Cols> mat{}, expected{};
            double scalar{distrib(gen)};

            for (auto i : std::views::iota(0uz, Rows)) {
                for (auto j : std::views::iota(0uz, Cols)) {
                    mat[i][j] = distrib(gen);
                    expected[i][j] = mat[i][j] / scalar;
                }
            }

            return mat / scalar == expected;
        }

    // FIXME: place this into its own namespace and then test each of these as
    // separate functions
    bool test_mat_mat_mult() {
        // TODO: These are all the functions that are required for testing
        // matrix multiplication
        // I should've made a better note when I wrote this.
        // Huh who knew writing an API would be so much work.

        // 1. rectangular multiplication
        // 2. identity matrix
        // 3. zero matrix
        // 4. negative values
        // 5. 1x1 matrix
        // 6. associativity
    }

    bool test_mat_vec_mult() {
        return false;
    }

    bool test_vec_mat_mult() {
        return false;
    }

    //bool test_component_mult
    //bool test_component_div
    //bool test_dot
    //bool test_distance
    //bool test_lerp
}; // namespace TMat

template <size_t Rows, size_t Cols>
std::array<unsigned int, 2> test_matrix_general() {
    /*
       returns the number of tests and the number of tests that failed
       */

    std::vector<TestCase> tests = {
        {"default constructor",             TMat::test_default_ctor<Rows, Cols>     },
        {"initializer list constructor",    TMat::test_init_list_ctor<Rows, Cols>   },
        {"equality",                        TMat::test_equality<Rows, Cols>         },
        {"inequality",                      TMat::test_inequality<Rows, Cols>       },
        {"addition",                        TMat::test_addition<Rows, Cols>         },
        {"subtraction",                     TMat::test_subtraction<Rows, Cols>      },
        {"scalar multiplication",           TMat::test_scalar_mult<Rows, Cols>      },
        {"scalar division",                 TMat::test_scalar_div<Rows, Cols>       },
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

// explicit instantiation of test_matrix_general (for testing)
template std::array<unsigned int, 2> test_matrix_general<3, 3>();
template std::array<unsigned int, 2> test_matrix_general<4, 4>();

namespace TMatMult {
    bool rectangular_multiplication() {
        Mat<3, 4> A{
            {
                {1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12}
            }
        };

        Mat<4, 3> B{
            {
                {13,14,15},
                    {16,17,18},
                    {19,20,21},
                    {22,23,24}
            }
        };

        Mat<3, 3> expected{
            {
                {190, 200, 210},
                    {470, 496, 522},
                    {750, 792, 834}
            }
        };

        return A * B == expected;
    }

    bool identity_matrix() {
        Mat<2, 3> A{
            {
                {1,2,3},
                    {4,5,6}
            }
        };
        Mat<3, 3> I = identity<3>();
        return A * I == A;
    }

    bool zero_matrix() {
        Mat<2, 2> A{
            {
                {1,2},
                    {3,4}
            }
        };
        Mat<2, 2> Zero{};
        return A * Zero == Zero;
    }

    bool negative_values() {
        Mat<2, 2> A{
            {
                {3,-3},
                    {-1,4}
            }
        };
        Mat<2, 2> B{
            {
                {-2,5},
                    {3,-1}
            }
        };
        Mat<2, 2> expected{
            {
                {-13,13},
                    {14,-9}
            }
        };
        return A * B == expected;
    }

    bool one_by_one_matrix() {
        Mat<1, 1> A{
            {
                {4}
            }
        };
        Mat<1, 1> B{
            {
                {5}
            }
        };
        Mat<1, 1> expected{
            {
                {20}
            }
        };
        return A * B == expected;
    }

    bool associativity() {
        Mat<2, 2> A{}, B{}, C{};
        for (size_t i{0}; i < 2; ++i) {
            for (size_t j{0}; j < 2; ++j) {
                A[i][j] = distrib(gen);
                B[i][j] = distrib(gen);
                C[i][j] = distrib(gen);
            }
        }
        return (A * B) * C == A * (B * C);
    }
}; // namespace TMatMult


// TODO: need to rewrite this after finishing TMatMult
// NOTE: I really don't like the way I broke this up. I might refactor everything
// before continuing to write this test honestly.
template<size_t Rows, size_t Inner, size_t Cols>
std::array<unsigned int, 2> test_matrix_multiplication() {
    std::vector<TestCase> tests = {
        {}
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

// explicit instantiation of test_matrix_multiplication (for testing)
template std::array<unsigned int, 2> test_matrix_multiplication<1,2,3>();
