#include <iostream>
#include <string>
#include <vector>

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
public:
    Point p;
    
    Rectangle(): p{0, 0} {}

    Rectangle(Point const &np): p{np.x, np.y} {}

    Rectangle operator+(Rectangle const &rha) const {
        return Rectangle((p.maxx(rha.p)).maxy(rha.p));
    }

    Rectangle operator*(Rectangle const &rha) const {
        return Rectangle((p.minx(rha.p)).miny(rha.p));
    }
    void print() const { p.print(); }
};

void translate(std::string expr, std::vector<int> &coord, std::vector<std::string> &oper) {
    for(int i = 0; i < expr.size(); i++) {
        if (expr[i] == '+') {
            oper.push_back("+");
        } else if (expr[i] == '*') {
            oper.push_back("*");
        } else if (expr[i] == '(') {
            int j = i;
            while(expr[j] != ',') {
                j++;
            }
            int k = j;
            while(expr[k] != ')') {
                k++;
            }
            coord.push_back(std::stoi(expr.substr(i + 1, j)));
            coord.push_back(std::stoi(expr.substr(j + 1, k)));
        }
    }
}

void iteration(std::vector<int> &coord, std::vector<std::string> &oper, int idx, bool mult) {
    Point p_1 = Point(coord[2 * idx], coord[2 * idx + 1]);
    Point p_2 = Point(coord[2 * idx + 2], coord[2 * idx + 3]);
    Rectangle r_1 = Rectangle(p_1);
    Rectangle r_2 = Rectangle(p_2);
    if (mult) {
        Rectangle r_3 = r_1 * r_2;
        coord[2 * idx] = r_3.p.x;
        coord[2 * idx + 1] = r_3.p.y;
    } else {
        Rectangle r_3 = r_1 + r_2;
        coord[2 * idx] = r_3.p.x;
        coord[2 * idx + 1] = r_3.p.y;
    }
    oper.erase(oper.begin() + idx);
    coord.erase(coord.begin() + 2 * idx + 2, coord.begin() + 2 * idx + 4);
}

void calculate(std::vector<int> &coord, std::vector<std::string> &oper) {
    for(int i = oper.size() - 1; i > -1; i--) {
        if (oper[i] == "*") {
            iteration(coord, oper, i, true);
        }
    }
    for(int i = oper.size() - 1; i > -1; i--) {
        iteration(coord, oper, i, false);
    }
}

int main() {
    std::string expr;
    std::getline(std::cin, expr);
    std::vector<int> coord(0);
    std::vector<std::string> oper(0);
    translate(expr, coord, oper);
    calculate(coord, oper);
    std::cout << "(" << coord[0] << "," << coord[1] << ")";
    return 0;
}
