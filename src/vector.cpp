#include "vector.h"

Vector::Vector()
: x{0}, y{0} {}

Vector::Vector(double x, double y)
: x{x}, y{y} {}

Vector& Vector::operator+=(Vector vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector& Vector::operator-=(Vector vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector& Vector::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector& Vector::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector operator+(Vector p1, const Vector& p2) {
    return p1 += p2;
}
Vector operator-(Vector p1, const Vector& p2) {
    return p1 -= p2;
}
Vector operator*(Vector p, double scalar) {
    return p *= scalar;
}
Vector operator/(Vector p, double scalar) {
    return p /= scalar;
}

double Vector::magnitude() {
    return sqrt(x * x + y * y);
}