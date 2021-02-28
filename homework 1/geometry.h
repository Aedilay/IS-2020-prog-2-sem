#ifndef MAIN_CPP_GEOMETRY_H
#define MAIN_CPP_GEOMETRY_H

#include <vector>
#include <cmath>

class Point {
private:
    long x_;
    long y_;

public:
    Point(long x, long y);

    Point();

    Point(const Point &point);

    Point &operator=(const Point &pointCopy);

    [[nodiscard]] long getX() const;

    [[nodiscard]] long getY() const;

};

class PolygonalChain {
protected:
    long size;
    std::vector<Point> vec;
public:

    PolygonalChain(long size, Point array[]);

    PolygonalChain(const PolygonalChain &polyChain);

    PolygonalChain &operator=(const PolygonalChain &polygonalChainCopy);

    [[nodiscard]] long getN() const;

    [[nodiscard]] Point getPoint(long position) const;

    [[nodiscard]] virtual double perimeter() const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain(long size, Point array[]);

    ClosedPolygonalChain(const ClosedPolygonalChain &other);

    [[nodiscard]] double perimeter() const override;
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon(long size, Point array[]);

    Polygon(const Polygon &other);

    [[nodiscard]] virtual double area() const;

    Polygon &operator=(const Polygon &polygonCopy);
};

class Triangle : public Polygon {
public:
    Triangle(long size, Point array[]);

    Triangle(const Triangle &other);

    Triangle &operator=(const Triangle &other);

    [[nodiscard]] bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid(long size, Point array[]);

    Trapezoid(const Trapezoid &other);

    Trapezoid &operator=(const Trapezoid &other);

    [[nodiscard]] double height() const;
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(long size, Point array[]);
    RegularPolygon(const RegularPolygon &other);
};

#endif //MAIN_CPP_GEOMETRY_H