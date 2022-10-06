#include <iostream>

class Cell 
{
private:
    int x;
    int y;
public:
    Cell(): x(1), y(1){}
    Cell(int x, int y): x(x), y(y) {}
    ~Cell() {}
    int get_x() const { return x; }
    int get_y() const { return y; }
};

class Piece 
{
protected:
    Cell c;
public:
    Piece(): c() {}
    Piece(Cell c): c(c) {}
    virtual ~Piece() {}
    virtual Cell position() const { return c; }
    virtual bool available(const Cell &c) const = 0;
};

class King: public Piece
{
public:
    King(): Piece() {}
    King(Cell c): Piece(c) {}
    ~King() override {}
    bool available(const Cell &c) const override
    {
        int dx = c.get_x() - position().get_x();
        int dy = c.get_y() - position().get_y();
        return dx * dx + dy * dy <= 2;
    } 
};

class Pawn: public Piece
{
public:
    Pawn(): Piece() {}
    Pawn(Cell c): Piece(c) {}
    ~Pawn() override {}
    bool available(const Cell &c) const override
    {
        int dx = c.get_x() - position().get_x();
        int dy = c.get_y() - position().get_y();
        return (dx == 0) and (dy == 0 or dy == 1);
    } 
};

class Bishop: public virtual Piece
{
public:
    Bishop(): Piece() {}
    Bishop(Cell c): Piece(c) {}
    ~Bishop() override {}
    bool available(const Cell &c) const override
    {
        int dx = c.get_x() - position().get_x();
        int dy = c.get_y() - position().get_y();
        return dx * dx == dy * dy;
    } 
};

class Rook: public virtual Piece
{
public:
    Rook(): Piece() {}
    Rook(Cell c): Piece(c) {}
    ~Rook() override {}
    bool available(const Cell &c) const override
    {
        int dx = c.get_x() - position().get_x();
        int dy = c.get_y() - position().get_y();
        return dx == 0 or dy == 0;
    } 
};

class Queen: public Bishop, public Rook
{
public:
    Queen(): Bishop(), Rook() {}
    Queen(Cell c): Bishop(c), Rook(c) {}
    ~Queen() override {} 
    bool available(const Cell &c) const override
    {
        return Rook::available(c) or Bishop::available(c);
    }
};

class Knight: public Piece
{
public:
    Knight(): Piece() {}
    Knight(Cell c): Piece(c) {}
    ~Knight() override {}
    bool available(const Cell &c) const override
    {
        int dx = c.get_x() - position().get_x();
        int dy = c.get_y() - position().get_y();
        return dx * dx + dy * dy == 5;
    } 
};

int main()
{   
    Cell c(1, 1);
    King p1(c);
    Pawn p2(c);
    Bishop p3(c);
    Rook p4(c);
    Queen p5(c);
    Knight p6(c);
    Cell c1(1, 2);
    Cell c2(1, 3);
    Cell c3(2, 3);
    Cell c4(3, 3);
    std::cout << p1.available(c1) << "\n"; //1
    std::cout << p1.available(c2) << "\n"; //0
    std::cout << p2.available(c1) << "\n"; //1
    std::cout << p2.available(c3) << "\n"; //0
    std::cout << p3.available(c4) << "\n"; //1
    std::cout << p3.available(c3) << "\n"; //0
    std::cout << p4.available(c2) << "\n"; //1
    std::cout << p4.available(c4) << "\n"; //0
    std::cout << p5.available(c4) << "\n"; //1
    std::cout << p5.available(c3) << "\n"; //0
    std::cout << p6.available(c3) << "\n"; //1
    std::cout << p6.available(c4) << "\n"; //0
    return 0;
}
