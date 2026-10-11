#include <array>
#include <format>
#include <print>

#include "tests/test_linear_algebra.h"

using Test = std::array<unsigned, 2>(*)(); // pointer to a function

unsigned run_test(Test test, std::string_view message) {
    std::println("CURRENT TEST : {}", message);

    std::array<unsigned, 2> result { test() };
    unsigned tests { result[0] };
    unsigned failed { result[1] };

    if (failed > 0) {
        std::string fail_log = std::format("Failed {} out of {} cases\n", failed, tests);
        log(fail_log, FAIL);
    }

    return failed;
}

int main() {
    unsigned fail {0};

    fail += run_test(test_vector<2>, "test_vector<2>");
    fail += run_test(test_vector<3>, "test_vector<3>");
    fail += run_test(test_vector<4>, "test_vector<4>");

    if (fail == 0) {
        std::string mesg = "All tests passed!";
        log(mesg, SUCCESS);
    }
    return 0;
}
