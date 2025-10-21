#pragma once
#include <cmath>

class Vector {
    public:
        Vector();
        Vector(double x, double y);
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;

        Vector& operator=(const Vector&) = default;
        Vector& operator+=(Vector vec);
        Vector& operator-=(Vector vec);
        Vector& operator*=(double scalar);
        Vector& operator/=(double scalar);

        double magnitude();

        double x;
        double y;
};