#include <print>
#include "tests/test_linear_algebra.h"

int main()
{
    int fail {0};

    // place tests here...
    fail += run_test_linear_algebra();

    if (fail == 0)
    {
        std::string mesg = "all tests passed!";
        log(mesg, SUCCESS);
    }
    else
    {
        std::string mesg = "some tests failed!";
        log(mesg, FAIL);
    }

    return 0;
}
