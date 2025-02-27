#include <cmath>
#include <iostream>

struct Point {
    double x, y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

/* PR: about encapsulation
 * This line representation is much complicated thing than the point
 * We can easily broke up invariants of this struct 
 * (it has only one invariant - equation a * x + b * y + c = 0 corresponds to line in 2D space)
 * First way - just create line like this Line(0.0, 0.0, 0.0)
 * Given equation will be equation of plane in 2D space
 * The same behavior will be in case of Line(p, p), where p - any point
 * See test samples
 */
struct Line {
    double a, b, c;

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
    Line(const Point& p1, const Point& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
    }
    
    /* PR: The same concern as above */ 
    Line(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    Point getIntersection(const Line& other) const {
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
