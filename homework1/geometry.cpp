#include "geometry.h"

Point::Point(long x, long y)
        : x_(x), y_(y) {}

Point::Point()
        : x_(0), y_(0) {}

Point::Point(const Point &point)
        : x_(point.x_), y_(point.y_) {}

Point &Point::operator=(const Point &pointCopy) {
    x_ = pointCopy.x_;
    y_ = pointCopy.y_;
    return *this;
}

long Point::getX() const {
    return x_;
}

long Point::getY() const {
    return y_;
}


PolygonalChain::PolygonalChain(long size_, Point array[]) {
    for (int i = 0; i < size_; i++) {
        vec.push_back(array[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain &other)
        : vec(other.vec) {}

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &other) {
    vec = other.vec;
    return *this;
}

PolygonalChain::~PolygonalChain() {
    vec.clear();
}

long PolygonalChain::getN() const {
    if (vec.at(0).getX() == vec.at(vec.size() - 1).getX() &&
        vec.at(0).getY() == vec.at(vec.size() - 1).getY())
        return (long) vec.size() - 1;
    return vec.size();
}

Point PolygonalChain::getPoint(long position) const {
    return vec.at(position);
}

double PolygonalChain::lenght(long i) const {
    return sqrt(pow(vec.at(i + 1).getX() - vec.at(i).getX(), 2) +
                pow(vec.at(i + 1).getY() - vec.at(i).getY(), 2));
}

double PolygonalChain::perimeter() const {
    double result = 0;
    for (int i = 0; i < (int) vec.size() - 1; ++i) {
        result += PolygonalChain::lenght(i);
    }
    return result;
}

ClosedPolygonalChain::ClosedPolygonalChain(long size, Point *array)
        : PolygonalChain(size, array) {
    vec.push_back(array[0]);
}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other)
        : PolygonalChain(other) {}

Polygon::Polygon(long size, Point *array)
        : ClosedPolygonalChain(size, array) {}

Polygon::Polygon(const Polygon &other)
        : ClosedPolygonalChain(other) {}

Polygon &Polygon::operator=(const Polygon &other) {
    vec = other.vec;
    return *this;
}

double Polygon::area() const {
    long result = 0;
    for (int i = 0; i < (int) vec.size() - 1; ++i)
        result += (vec.at(i + 1).getX() - vec.at(i).getX()) * (vec.at(i + 1).getY() + vec.at(i).getY());
    return (double) std::abs(result) / 2;
}

Triangle::Triangle(long size, Point *array)
        : Polygon(size, array) {}


Triangle::Triangle(const Triangle &other)
        : Polygon(other) {}

Triangle &Triangle::operator=(const Triangle &other) {
    vec = other.vec;
    return *this;
}

bool Triangle::hasRightAngle() const {
    auto vector1 = Point(vec.at(0).getX() - vec.at(1).getX(),
                         vec.at(0).getY() - vec.at(1).getY());

    auto vector2 = Point(vec.at(1).getX() - vec.at(2).getX(),
                         vec.at(1).getY() - vec.at(2).getY());

    auto vector3 = Point(vec.at(2).getX() - vec.at(0).getX(),
                         vec.at(2).getY() - vec.at(0).getY());

    return (vector1.getX() * vector2.getX() - vector1.getY() * vector2.getY() == 0 ||
            vector2.getX() * vector3.getX() - vector2.getY() * vector3.getY() == 0 ||
            vector3.getX() * vector1.getX() - vector3.getY() * vector1.getY() == 0);
}

Trapezoid::Trapezoid(long size, Point *array)
        : Polygon(size, array) {}

Trapezoid::Trapezoid(const Trapezoid &other)
        : Polygon(other) {}


Trapezoid &Trapezoid::operator=(const Trapezoid &other) {
    vec = other.vec;
    return *this;
}

double Trapezoid::height() const {
    double a = sqrt(pow((vec.at(2).getX() - vec.at(1).getX()), 2) -
                    pow((vec.at(2).getY() - vec.at(1).getY()), 2));
    double b = sqrt(pow((vec.at(4).getX() - vec.at(3).getX()), 2) -
                    pow((vec.at(4).getY() - vec.at(3).getY()), 2));
    double result = 2 * Polygon::area() / (a + b);
    return result;
}

RegularPolygon::RegularPolygon(long size, Point *array)
        : Polygon(size, array) {
}

RegularPolygon::RegularPolygon(const RegularPolygon &other)
        : Polygon(other) {}

double RegularPolygon::perimeter() const {
    return PolygonalChain::lenght() * ((int) vec.size() - 1);
}
//fixed kek
double RegularPolygon::area() const {
    return getN() * pow(PolygonalChain::lenght(), 2) / (4 * tan(M_PI / getN()));
}