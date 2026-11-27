// standard
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <print>
#include <random>
#include <utility>
#include <vector>

// custom
#include "math/linalg.h"
#include "util/log.h"

namespace TVec{
    template <std::size_t N>
    bool test_default_ctor();

    template <std::size_t N>
    bool test_arr_ctor();

    template <std::size_t N>
    bool test_bracket();

    template <std::size_t N>
    bool test_accessor();

    template <std::size_t N>
    bool test_equality();

    template <std::size_t N>
    bool test_inequality();

    template <std::size_t N>
    bool test_addition();

    template <std::size_t N>
    bool test_subtraction();

    template <std::size_t N>
    bool test_scalar_mult();

    template <std::size_t N>
    bool test_scalar_div();

    template <std::size_t N>
    bool test_component_mult();

    template <std::size_t N>
    bool test_component_div();

    template <std::size_t N>
    bool test_dot();

    template <std::size_t N>
    bool test_distance();

    template <std::size_t N>
    bool test_lerp();
}; // TVec

namespace TMat {
    template<size_t Rows, size_t Cols>
    bool test_default_ctor();

    template<size_t Rows, size_t Cols>
    bool test_init_list_ctor();
}; // TMat

template <std::size_t N>
std::array<unsigned, 2> test_vector();

template <size_t Rows, size_t Cols>
std::array<unsigned, 2> test_matrix_general();

template <size_t Rows, size_t Inner, size_t Cols>
std::array<unsigned, 2> test_matrix_multiplication();
