#include <iostream>

struct Point {
    unsigned long long const x, y;

    Point(unsigned long long x, unsigned long long y): x(x), y(y) {}

    Point minx(Point const &rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const &rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const &rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const {
        std::cout << '(' << x << ',' << y << ')';
    }
};

class Rectangle {
    Point p;
    
public:
    Rectangle(): p{0, 0} {}
    
    Rectangle(Point const &np): p{np.x, np.y} {} 
    
    Rectangle operator+(Rectangle const &rha) const {
        return (p.maxx(rha.p)).maxy(rha.p);
    }
    
    Rectangle operator*(Rectangle const &rha) const {
        return (p.minx(rha.p)).miny(rha.p);
    }
    void print() const { p.print(); }
};

int main() {
    Point p_A = Point(1, 2);
    Point p_B = Point(2, 1);
    Rectangle A = Rectangle(p_A);
    Rectangle B = Rectangle(p_B);
    Rectangle C = A + B;
    Rectangle D = A * B;
    C.print();
    D.print();
    return 0;
}
