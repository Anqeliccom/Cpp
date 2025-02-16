#include <iostream>

struct Point {
    double x, y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

struct Line {
    double a, b, c;

    Line(const Point& p1, const Point& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
    }

    Line(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    Point getIntersection(const Line& other) const {
        double det = a * other.b - other.a * b;

        if (det == 0) {
            if (a * other.c == c * other.a && b * other.c == c * other.b) {
                std::cerr << "The lines match." << std::endl;
            } else {
                std::cerr << "The lines ara parallel." << std::endl;
            }
            throw std::runtime_error("There are no intersections or infinitely many.");
        }
        double x = (b * other.c - other.b * c) / det;
        double y = (other.a * c - a * other.c) / det;
        return Point(x, y);
    }

    Line getPerpendicular(const Point& p) const {
        return Line(b, -a, -b * p.x + a * p.y);
    }
};
