#ifndef LINES_HPP
#define LINES_HPP

#include <optional>

constexpr double EPS = 1e-9;

bool isEqual(double a, double b);

struct Point {
    double x, y;
    Point(double x, double y);
};

struct Line {
    double a, b, c;

    Line(const Point& p1, const Point& p2);
    Line(double a, double b, double c);
    static std::optional<Line> create(const Point& p1, const Point& p2);
    static std::optional<Line> create(double a, double b, double c);

    [[nodiscard]] std::optional<Point> getIntersection(const Line& other) const;
    [[nodiscard]] Line getPerpendicular(const Point& p) const;
};

#endif // LINES_HPP
