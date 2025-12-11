#include "vector.h"

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

double Vector::magnitudeSquared() {
    return x * x + y * y;
}
