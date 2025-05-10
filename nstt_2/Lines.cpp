#include <cmath>
#include "Lines.hpp"

bool isEqual(double a, double b) {
    return std::fabs(a - b) < EPS;
}

Point::Point(double x, double y) : x(x), y(y) {}

/* PR: about encapsulation
 * This line representation is much complicated thing than the point
 * We can easily broke up invariants of this struct 
 * (it has only one invariant - equation a * x + b * y + c = 0 corresponds to line in 2D space)
 * First way - just create line like this Line(0.0, 0.0, 0.0)
 * Given equation will be equation of plane in 2D space
 * The same behavior will be in case of Line(p, p), where p - any point
 * See test samples
 */

/* PR: constructor fix
* Let's try to fix this encapsulation issue
* I saw that you used exceptions in your code,
* but throwing exceptions in constructors
* is a little bit tricky
* (but possible and good way (if it is written right)) thing
*
* I suggest you to avoid them, try to use `std::optional`
* and some OOP
* Note: if you can't come up with solution - feel free to text me
*/

Line::Line(const Point& p1, const Point& p2) : a(p2.y - p1.y), b(p1.x - p2.x), c(p2.x * p1.y - p1.x * p2.y) {}

Line::Line(double a, double b, double c) : a(a), b(b), c(c) {}

std::optional<Line> Line::create(const Point& p1, const Point& p2) {
    if (isEqual(p1.x, p2.x) && isEqual(p1.y, p2.y)) {
        return std::nullopt;
    }
    return Line(p1, p2);
}

std::optional<Line> Line::create(double a, double b, double c) {
    if (isEqual(a, 0) && isEqual(b, 0)) {
        return std::nullopt;
    }
    return Line(a, b, c);
}

std::optional<Point> Line::getIntersection(const Line& other) const {
    double det = a * other.b - other.a * b;

    /* PR: floats are tricky
    * comparing floating point numbers using '==' operator is almost always wrong
    * For see that go to tests
    *
    * The usual way (and correct in some sence) to implement floats comparison
    * is creation of function that works in this way `a == b <=> |a - b| < eps`
    * where eps is some precision of your computations
    *
    * Let's implement function that provides such functionallity.
    * And then I suggest you to use implemented function to compare all floats in your code
    *
    * Note: if something is unclear - please write to me
    */
    if (isEqual(det, 0)) {
        return std::nullopt;
    }
    double x = (b * other.c - other.b * c) / det;
    double y = (other.a * c - a * other.c) / det;
    return Point(x, y);
}

Line Line::getPerpendicular(const Point& p) const {
    return {b, -a, -b * p.x + a * p.y};
}
