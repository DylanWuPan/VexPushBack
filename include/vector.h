#pragma once
#include <cmath>

class Vector {
    public:
        constexpr Vector() noexcept
        : x{0}, y{0} {}
        constexpr Vector(double x, double y) noexcept
        : x{x}, y{y} {}
        constexpr Vector(const Vector&) noexcept = default;
        constexpr Vector(Vector&&) noexcept = default;

        Vector& operator=(const Vector&) = default;
        Vector& operator+=(Vector vec);
        Vector& operator-=(Vector vec);
        Vector& operator*=(double scalar);
        Vector& operator/=(double scalar);

        double magnitude();

        double x;
        double y;
};

Vector operator+(Vector p1, const Vector& p2);
Vector operator-(Vector p1, const Vector& p2);
Vector operator*(Vector p, double scalar);
Vector operator/(Vector p, double scalar);