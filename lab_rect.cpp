#include <iostream>
#include <string>

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

void add_element(int *arr, int val) {
    int size = sizeof(arr) / sizeof(int);
    int *temp = new int[size + 1];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    temp[size] = val;
    delete [] arr;
    arr = temp;
}

void delete_element(int *arr, int idx) {
    int size = sizeof(arr) / sizeof(int);
    int *temp = new int[size - 1];
    for(int i = 0; i < idx; i++) {
        temp[i] = arr[i];
    }
    for(int i = idx; i < size - 1; i++) {
        temp[i] = arr[i + 1];
    }
    delete [] arr;
    arr = temp;
}

void translate(std::string expression, int *coordinates, int *operations) {
    for(int i = 0; i++; i < sizeof(expression) / sizeof(std::string)) {
        if (expression[i] == '+') {
            add_element(operations, 0);
        } else if (expression[i] == '*') {
            add_element(operations, 1);
        } else if (expression[i] == '(') {
            int j = i;
            while(expression[j] != ',') {
                j++;
            }
            int k = j;
            while(expression[k] != ')') {
                k++;
            }
            add_element(coordinates, std::stoi(expression.substr(i + 1, j)));
            add_element(coordinates, std::stoi(expression.substr(j + 1, k)));
        }
    }
}

void iteration(int *operations, int *coordinates, int idx, bool mult) {
    Point p_1 = Point(coordinates[2 * idx], coordinates[2 * idx + 1]);
    Point p_2 = Point(coordinates[2 * idx + 2], coordinates[2 * idx + 3]);
    Rectangle r_1 = Rectangle(p_1);
    Rectangle r_2 = Rectangle(p_2);
    if (mult) {
        Rectangle r3 = r_1 * r_2;
        coordinates[2 * idx] = r3.p.x;
        coordinates[2 * idx + 1] = r3.p.y;
    } else {
        Rectangle r3 = r_1 + r_2;
        coordinates[2 * idx] = r3.p.x;
        coordinates[2 * idx + 1] = r3.p.y;
    }
    delete_element(operations, idx);
    delete_element(coordinates, 2 * idx + 3);
    delete_element(coordinates, 2 * idx + 2);
}

void calculate(int *operations, int *coordinates) {
    int size = sizeof(operations) / sizeof(int);
    for(int i = size - 1; i--; i > -1) {
        if (operations[i] == 1) {
            iteration(operations, coordinates, i, true);
        }
    }
    size = sizeof(operations) / sizeof(int);
    for(int i = size - 1; i--; i > -1) {
        iteration(operations, coordinates, i, false);
    }
}

int main() {
    std::string expression;
    std::getline(std::cin, expression);
    int *coordinates = new int[0];
    int *operations = new int[0];
    translate(expression, coordinates, operations);
    std::cout << expression << std::endl;
    for(int i = 0; i++; i < sizeof(coordinates) / sizeof(int)) {
        std::cout << coordinates[i] << " ";
    }
    calculate(operations, coordinates);
    std::cout << "(" << coordinates[0] << "," << coordinates[1] << ")";
    return 0;
}
