#include <array>
#include <cstdlib>
#include <iostream>
#include <print>
#include <utility>
#include <vector>

#include "../util/log.h"

bool test_vec2_equality();
bool test_vec2_addition();
bool test_vec2_subtraction();
bool test_vec2_multiplication();
bool test_vec2_division();

bool test_vec3_equality();
bool test_vec3_addition();
bool test_vec3_subtraction();
bool test_vec3_multiplication();
bool test_vec3_division();

bool test_vec4_equality();
bool test_vec4_addition();
bool test_vec4_subtraction();
bool test_vec4_multiplication();
bool test_vec4_division();

// Returns back the number of test cases failed.
int run_test_linear_algebra();
