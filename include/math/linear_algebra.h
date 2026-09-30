/*
   Header-only, custom linear algebra library
   */

#pragma once

/* NOTE: removing inline can be useful for debugging compiler behavior / benchmarking
   or just letting the compiler do its thang.
   */

#ifdef DO_NOT_DECLARE_INLINE
#define STATIC_INLINE static
#else
#define STATIC_INLINE static inline
#endif

// FIXME: The multiplication and divison operations are HADAMARD ops.
//  Not technically correct for the use case. Replace so that  
//  operation* and operation/, and other respective overloads, so that
//  they represent vector (x) scalar.

// Just rename the current overloaded operations as *hadamard-mult* and *hadamard-div*

/*
   TODO: version 1.0 targets to implement.

    Vec2 ─┐
    Vec3 ─┼─ arithmetic (add, subtract, multiply, divide) [x]
    Vec4 ─┘
        ├─ dot
        ├─ cross (Vec3)
        ├─ length / normalize
        ├─ distance
        └─ lerp

    Mat3 ─┐
    Mat4 ─┼─ arithmetic
        ├─ matrix multiplication
        ├─ vector multiplication
        ├─ transpose
        ├─ determinant
        └─ inverse

    Mat4 ── translation
        ── rotation
        ── scale
        ── perspective
        ── orthographic
        └── look_at

    Utilities
        ├── radians / degrees
        ├── clamp
        ├── lerp
        └── transform_point/vector
        */

struct Vec2
{
    double x, y;

    Vec2() : x(0.0), y(0.0) {}
    Vec2(const double _x, const double _y) : x(_x), y(_y) {}

    // equality
    bool operator==(const Vec2& V) const
    {
        return x == V.x
            && y == V.y;
    }
    bool operator!=(const Vec2& V) const
    {
        return x != V.x
            || y != V.y;
    }

    // addition
    Vec2 operator+(const Vec2& V) const
    {
        return Vec2
        {
            x + V.x,
            y + V.y
        };
    }
    void operator+=(const Vec2& V)
    {
        x += V.x;
        y += V.y;
    }

    // subtraction
    Vec2 operator-(const Vec2& V) const
    {
        return Vec2
        {
            x - V.x,
            y - V.y
        };
    }
    void operator-=(const Vec2& V)
    {
        x -= V.x;
        y -= V.y;
    }

    // multiplication
    Vec2 hadamard_mult(const Vec2& V)
    {
        return Vec2
        {
            x * V.x,
            y * V.y
        };
    }

    // division
    Vec2 hadamard_div(const Vec2& V)
    {
        return Vec2
        {
            x / V.x,
            y / V.y
        };
    }
};

struct Vec3
{
    double x, y, z;
    Vec3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    Vec3(const double x, const double y, const double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // equality
    bool operator==(const Vec3& V) const
    {
        return x == V.x
            && y == V.y
            && z == V.z;
    }
    bool operator!=(const Vec3& V) const
    {
        return x != V.x
            || y != V.y
            || z != V.z;
    }

    // addition
    Vec3 operator+(const Vec3& V) const
    {
        return Vec3
        {
            x + V.x,
            y + V.y,
            z + V.z
        };
    }
    void operator+=(const Vec3& V)
    {
        x += V.x;
        y += V.y;
        z += V.z;
    }

    // subtraction
    Vec3 operator-(const Vec3& V) const
    {
        return Vec3
        {
            x - V.x,
            y - V.y,
            z - V.z
        };
    }
    void operator-=(const Vec3& V)
    {
        x -= V.x;
        y -= V.y;
        z -= V.z;
    }

    // multiplication
    Vec3 hadamard_mult(const Vec3& V)
    {
        return Vec3
        {
            x * V.x,
            y * V.y,
            z * V.z
        };
    }

    // division
    Vec3 hadamard_div(const Vec3& V)
    {
        return Vec3
        {
            x / V.x,
            y / V.y,
            z / V.z
        };
    }
};

struct Vec4
{
    double x, y, z, w;
    Vec4()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        w = 0.0;
    }
    Vec4(const double x, const double y, const double z, const double w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    // equality
    bool operator==(const Vec4& V) const
    {
        return x == V.x
            && y == V.y
            && z == V.z
            && w == V.w;
    }
    bool operator!=(const Vec4& V) const
    {
        return x != V.x
            || y != V.y
            || z != V.z
            || w != V.w;
    }

    // addition
    Vec4 operator+(const Vec4& V) const
    {
        return Vec4
        {
            x + V.x,
            y + V.y,
            z + V.z,
            w + V.w
        };
    }
    void operator+=(const Vec4& V)
    {
        x += V.x;
        y += V.y;
        z += V.z;
        w += V.w;
    }

    // subtraction
    Vec4 operator-(const Vec4& V) const
    {
        return Vec4
        {
            x - V.x,
            y - V.y,
            z - V.z,
            w - V.w,
        };
    }
    void operator-=(const Vec4& V)
    {
        x -= V.x;
        y -= V.y;
        z -= V.z;
        w -= V.w;
    }

    // multiplication
    Vec4 hadamard_mult(const Vec4& V)
    {
        return Vec4
        {
            x * V.x,
            y * V.y,
            z * V.z,
            w * V.w
        };
    }

    // division
    Vec4 hadamard_div(const Vec4& V)
    {
        return Vec4
        {
            x / V.x,
            y / V.y,
            z / V.z,
            w / V.w
        };
    }
};
