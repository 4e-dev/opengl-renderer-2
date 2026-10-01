#include "math/linear_algebra.h"
#include "tests/test_linear_algebra.h"

// FIXME: likely need to throw this into a base test class...
using Test = bool(*)(); // pointer to a function that returns a bool.
struct TestCase {
    std::string name;
    Test test;
};

using ar2 = std::array<double, 2>;
using ar3 = std::array<double, 3>;
using ar4 = std::array<double, 4>;

namespace TestVec2
{
    bool equal()
    {
        const ar2 x{1.0, 2.0};
        const ar2 y{3.0, 5.0};

        if (x != x)
            return false;

        if (x == y || y == x)
            return false;

        return x != y && y != x;
    }

    bool add()
    {
        const ar2 x{1.0, 2.0};
        const ar2 y{3.0, 5.0};

        Vec2 a{x[0], x[1]};
        Vec2 b{y[0], y[1]};
        Vec2 c
        {
            x[0] + y[0],
            x[1] + y[1]
        };

        if (a + b != c)
            return false;

        a += b;
        if (a != c)
            return false;

        return true;
    }

    bool sub()
    {
        const ar2 x{1.0, 2.0};
        const ar2 y{3.0, 5.0};

        Vec2 a{x[0], x[1]};
        Vec2 b{y[0], y[1]};
        Vec2 c
        {
            x[0] - y[0],
            x[1] - y[1]
        };

        if (a - b != c)
            return false;

        a -= b;
        if (a != c)
            return false;

        return true;
    }

    bool hadamard_mult()
    {
        const ar2 x{1.0, 2.0};
        const ar2 y{3.0, 5.0};

        Vec2 a{x[0], x[1]};
        Vec2 b{y[0], y[1]};
        Vec2 c
        {
            x[0] * y[0],
            x[1] * y[1]
        };

        return a.hadamard_mult(b) == c;
    }

    bool hadamard_div()
    {
        const ar2 x{1.0, 2.0};
        const ar2 y{3.0, 5.0};

        Vec2 a{x[0], x[1]};
        Vec2 b{y[0], y[1]};
        Vec2 c
        {
            x[0] / y[0],
            x[1] / y[1]
        };

        return a.hadamard_div(b) == c;
    }

    bool scalar_mult()
    {
        const Vec2 a{1.0, 2.0};
        const double scalar = 69.69;
        const Vec2 b
        {
            a.x * scalar,
            a.y * scalar
        };
        return a * scalar == b;
    }

    bool scalar_div()
    {
        const Vec2 a{1.0, 2.0};
        const double scalar = 69.69;
        const Vec2 b
        {
            a.x / scalar,
            a.y / scalar
        };
        return a / scalar == b;
    }
} // namespace TestVec2

namespace TestVec3 {
    bool equal()
    {
        const ar3 x{1.0, 2.0, 3.0};
        const ar3 y{5.0, 8.0, 13.0};

        if (x != x)
            return false;

        if (x == y || y == x)
            return false;

        return x != y && y != x;
    }

    bool add()
    {
        const ar3 x{1.0, 2.0, 3.0};
        const ar3 y{5.0, 8.0, 13.0};

        Vec3 a{x[0], x[1], x[2]};
        Vec3 b{y[0], y[1], y[2]};
        Vec3 c
        {
            x[0] + y[0],
            x[1] + y[1],
            x[2] + y[2],
        };

        if (a + b != c)
            return false;

        a += b;
        if (a != c)
            return false;

        return true;
    }

    bool sub()
    {
        const ar3 x{1.0, 2.0, 3.0};
        const ar3 y{5.0, 8.0, 13.0};

        Vec3 a{x[0], x[1], x[2]};
        Vec3 b{y[0], y[1], y[2]};
        Vec3 c
        {
            x[0] - y[0],
            x[1] - y[1],
            x[2] - y[2],
        };

        if (a - b != c)
            return false;

        a -= b;
        if (a != c)
            return false;

        return true;
    }

    bool hadamard_mult()
    {
        const ar3 x{1.0, 2.0, 3.0};
        const ar3 y{5.0, 8.0, 13.0};

        Vec3 a{x[0], x[1], x[2]};
        Vec3 b{y[0], y[1], y[2]};
        Vec3 c
        {
            x[0] * y[0],
            x[1] * y[1],
            x[2] * y[2],
        };

        return a.hadamard_mult(b) == c;
    }

    bool hadamard_div()
    {
        const ar3 x{1.0, 2.0, 3.0};
        const ar3 y{5.0, 8.0, 13.0};

        Vec3 a{x[0], x[1], x[2]};
        Vec3 b{y[0], y[1], y[2]};
        Vec3 c
        {
            x[0] / y[0],
            x[1] / y[1],
            x[2] / y[2],
        };

        return a.hadamard_div(b) == c;
    }

    bool scalar_mult()
    {
        const Vec3 a{1.0, 2.0, 3.0};
        const double scalar = 69.69;
        const Vec3 b
        {
            a.x * scalar,
            a.y * scalar,
            a.z * scalar
        };
        return a * scalar == b;
    }

    bool scalar_div()
    {
        const Vec3 a{1.0, 2.0, 3.0};
        const double scalar = 69.69;
        const Vec3 b
        {
            a.x / scalar,
            a.y / scalar,
            a.z / scalar
        };
        return a / scalar == b;
    }
} // namespace TestVec3

namespace TestVec4 {
    bool equal()
    {
        const ar4 x{1.0, 2.0, 3.0, 5.0};
        const ar4 y{8.0, 13.0, 21.0, 34.0};

        if (x != x)
            return false;

        if (x == y || y == x)
            return false;

        return x != y && y != x;
    }

    bool add()
    {
        const ar4 x{1.0, 2.0, 3.0, 5.0};
        const ar4 y{8.0, 13.0, 21.0, 34.0};

        Vec4 a{x[0], x[1], x[2], x[3]};
        Vec4 b{y[0], y[1], y[2], y[3]};
        Vec4 c
        {
            x[0] + y[0],
            x[1] + y[1],
            x[2] + y[2],
            x[3] + y[3]
        };

        if (a + b != c)
            return false;

        a += b;
        if (a != c)
            return false;

        return true;
    }

    bool sub()
    {
        const ar4 x{1.0, 2.0, 3.0, 5.0};
        const ar4 y{8.0, 13.0, 21.0, 34.0};

        Vec4 a{x[0], x[1], x[2], x[3]};
        Vec4 b{y[0], y[1], y[2], y[3]};
        Vec4 c
        {
            x[0] - y[0],
            x[1] - y[1],
            x[2] - y[2],
            x[3] - y[3]
        };

        if (a - b != c)
            return false;

        a -= b;
        if (a != c)
            return false;

        return true;
    }

    bool hadamard_mult()
    {
        const ar4 x{1.0, 2.0, 3.0, 5.0};
        const ar4 y{8.0, 13.0, 21.0, 34.0};

        Vec4 a{x[0], x[1], x[2], x[3]};
        Vec4 b{y[0], y[1], y[2], y[3]};
        Vec4 c
        {
            x[0] * y[0],
            x[1] * y[1],
            x[2] * y[2],
            x[3] * y[3]
        };

        return a.hadamard_mult(b) == c;
    }

    bool hadamard_div()
    {
        const ar4 x{1.0, 2.0, 3.0, 5.0};
        const ar4 y{8.0, 13.0, 21.0, 34.0};

        Vec4 a{x[0], x[1], x[2], x[3]};
        Vec4 b{y[0], y[1], y[2], y[3]};
        Vec4 c
        {
            x[0] / y[0],
            x[1] / y[1],
            x[2] / y[2],
            x[3] / y[3]
        };

        return a.hadamard_div(b) == c;
    }

    bool scalar_mult()
    {
        const Vec4 a{1.0, 2.0, 3.0, 5.0};
        const double scalar = 69.69;
        const Vec4 b
        {
            a.x * scalar,
            a.y * scalar,
            a.z * scalar,
            a.w * scalar
        };
        return a * scalar == b;
    }

    bool scalar_div()
    {
        const Vec4 a{1.0, 2.0, 3.0, 5.0};
        const double scalar = 69.69;
        const Vec4 b
        {
            a.x / scalar,
            a.y / scalar,
            a.z / scalar,
            a.w / scalar
        };
        return a / scalar == b;
    }
} // namespace TestVec4

int run_test_linear_algebra()
{
    std::vector<TestCase> tests = {
        {"Vec2::equal", TestVec2::equal},
        {"Vec3::equal", TestVec3::equal},
        {"Vec4::equal", TestVec4::equal},
        {"Vec2::add", TestVec2::add},
        {"Vec3::add", TestVec3::add},
        {"Vec4::add", TestVec4::add},
        {"Vec2::sub", TestVec2::sub},
        {"Vec3::sub", TestVec3::sub},
        {"Vec4::sub", TestVec4::sub},
        {"Vec2::hadamard_mult", TestVec2::hadamard_mult},
        {"Vec3::hadamard_mult", TestVec3::hadamard_mult},
        {"Vec4::hadamard_mult", TestVec4::hadamard_mult},
        {"Vec2::hadamard_div", TestVec2::hadamard_div},
        {"Vec3::hadamard_div", TestVec3::hadamard_div},
        {"Vec4::hadamard_div", TestVec4::hadamard_div},
        {"Vec2::scalar_mult", TestVec2::scalar_mult},
        {"Vec3::scalar_mult", TestVec3::scalar_mult},
        {"Vec4::scalar_mult", TestVec4::scalar_mult},
        {"Vec2::scalar_div", TestVec2::scalar_div},
        {"Vec3::scalar_div", TestVec3::scalar_div},
        {"Vec4::scalar_div", TestVec4::scalar_div}
    };

    int num_tests_failed {0};

    for (const auto& t : tests)
    {
        if (!t.test())
        {
            std::string mesg = std::format("{} failed", t.name);
            log(mesg, ERROR, __FILE__, __LINE__);
            ++num_tests_failed;
        }
        else
        {
            std::string mesg = std::format("{} passed", t.name);
            log(mesg, SUCCESS);
        }
    }

    if (num_tests_failed > 0)
    {
        std::string mesg = std::format("run_test_linear_algebra: {} tests failed", num_tests_failed);
        log(mesg, ERROR, __FILE__, __LINE__);
    }

    return num_tests_failed;
}
