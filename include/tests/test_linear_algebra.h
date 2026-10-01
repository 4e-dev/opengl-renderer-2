#include <array>
#include <cstdlib>
#include <iostream>
#include <print>
#include <utility>
#include <vector>

#include "../util/log.h"

namespace TestVec2
{
    bool equal();
    bool add();
    bool sub();
    bool hadamard_mult();
    bool hadamard_div();
    bool scalar_mult();
    bool scalar_div();
}

namespace TestVec3
{
    bool equal();
    bool add();
    bool sub();
    bool hadamard_mult();
    bool hadamard_div();
    bool scalar_mult();
    bool scalar_div();
}

namespace TestVec3
{
    bool equal();
    bool add();
    bool sub();
    bool hadamard_mult();
    bool hadamard_div();
    bool scalar_mult();
    bool scalar_div();
}

// Returns back the number of test cases failed.
int run_test_linear_algebra();
