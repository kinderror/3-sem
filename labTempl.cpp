#include<iostream>

template <typename T> 
struct Comparator 
{
    virtual bool operator()(T const &lha, T const &rha) const = 0; 
};

struct IntComparator final: Comparator<int> 
{
    bool operator()(int const &lha , int const &rha) const override
    {
        return lha < rha;
    }
};

template<typename T>
int partition_by_number(Comparator<T> &compare, T *buffer, int left, int right) 
{
    T pivot = buffer[(left + right) / 2];
    while(true) 
    {
        while (left < sizeof(buffer) - 1 && compare(buffer[left], pivot)) left++;
        while (right > 0 && compare(pivot, buffer[right])) right--;
        if (left >= right) return right;
        std::swap(buffer[left], buffer[right]);
        if (left < sizeof(buffer) - 1) left++;
        if (right > 0) right--;
        for(int i = 0; i < 10; i++)
        {
            std::cout << buffer[i] << " ";
        }
    }
}

template<typename T>
void quick_sort(Comparator<T> &compare, T *buffer, int left, int right) {
    if (left >= right) {
        return;
    }
    int split = partition_by_number(compare, buffer, left, right);
    quick_sort(compare, buffer, left, split);
    quick_sort(compare, buffer, split++, right);
}

int main()
{
    std::cout << "sth";
    IntComparator compare = IntComparator();
    int *buffer = new int[10];
    for(int i = 0; i < 10; i++)
    {
        buffer[i] = 10 - i;
    }
    std::cout << "sth";
    quick_sort<int>(compare, buffer, 0, 9);
    for(int i = 0; i < 10; i++)
    {
        std::cout << buffer[i] << " ";
    }
    return 0;
}
