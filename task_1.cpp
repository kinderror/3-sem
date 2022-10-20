#include<iostream>

template <typename T>
class Array
{
private:
    size_t buffer_size;
    T *buffer;
public:
    // конструктор 
    explicit Array(size_t buffer_size, const T &buffer):
        buffer_size(buffer_size), buffer(buffer) {}  
    // конструктор копирования
    Array(const Array &src): 
        Array(src.buffer_size, new T[src.buffer_size])
    {
        for (size_t pos = 0; pos != buffer_size; pos++)
        {
            buffer[pos] = src.buffer[pos];
        }
    } 
    //конструктор перемещения
    Array(const Array &&src): 
        Array(src.buffer_size, src.buffer)
    {
        src.buffer_size = 0;
        src.buffer = nullptr;
    }
    // деструктор
    ~Array() { delete[] buffer; }
    // оператор копирующего присваивания
    Array& operator=(const Array &src)
    {
        if (&src == this) { return *this; }
        Array<T> tmp(src);
        std::swap(this->buffer, tmp.buffer);
        std::swap(this->buffer_size, tmp.buffer_size);
    }
    // оператор перемещающего присваивания
    Array& operator=(const Array &&src)
    {
        Array<T> tmp(std::move(src));
        std::swap(this->buffer_size, buffer_size);
        std::swap(this->buffer, src.buffer);
    }
    // возвращает размер массива (кол-во элементов)
    size_t size() const { return this->buffer_size; }
    // две версии оператора доступа по индексу
    T& operator[](size_t idx) { return buffer[idx]; }
    const T& operator[](size_t idx) const { return buffer[idx]; }
    // метод вывода массива
    void print()
    {
        for(size_t pos = 0; pos != buffer_size; pos++)
        {
            std::cout << buffer[pos] << " ";
        }
        std::cout << "\n";
    }
};

int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int b[3] = {3, 2, 1};
    size_t s_1 = 5, s_2 = 3;
    Array<int> A(s_1, a);
    Array<int> B(s_2, b);
    Array<int> C(A); // конструктор копирования
    Array<int> D(B); // конструктор перемещения
    С = B; // оператор копирующего присваивания
    D = std::move(A); // оператор перемещающего присваивания
    A.print();
    B.print();
    C.print();
    D.print(); 
}

