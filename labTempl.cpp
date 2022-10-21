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

template<typename T>
class PriorityQueue
{
private:
    T *buffer;
    Comparator<T> &compare;
public:
    PriorityQueue(Comparator<T> &compare): 
        buffer(new T[0]), compare(compare) {}
    void push(T value)
    {
        int idx = 0, size = sizeof(buffer);
        T *temp = new T[size + 1];
        for(; idx < size; idx++)
        {
            temp[idx] = buffer[idx];
        }
        temp[idx++] = value;
        while(idx > 0 && 
            compare(temp[(idx - 1) / 2], temp[idx]))
        {
            std::swap(temp[(idx - 1) / 2], temp[idx]);
            idx = (idx - 1) / 2;
        }
        delete [] buffer;
        buffer = temp;
    }
    void heapify()
    {
        int idx = 0, left = 1, right = 2,
            largest = 0, size = sizeof(buffer);
        
        while(true)
        {
            if(left < size && 
                compare(buffer[largest], buffer[left]))
            {
                largest = left;
            }
            if(right < size &&
                compare(buffer[largest], buffer[right]))
            {
                largest = right;
            }
            if(largest == idx) return;
            std::swap(buffer[idx], buffer[largest]);
            idx = largest;
        }
    }
    void poll()
    {
        int size = sizeof(buffer);
        std::swap(buffer[0], buffer[size - 1]);
        T *temp = new T[size - 1];
        for(int idx; idx < size - 1; idx++)
        {
            temp[idx] = buffer[idx];
        }
        delete [] buffer;
        buffer = temp;
        heapify();
    }
    void print() const
    {
        for(int idx = 0; idx < sizeof(buffer); idx++)
        {
            std::cout << buffer[idx] << " ";
        }
        std::cout << "\n";
    }
    T peek() const { return buffer[0]; }
    bool is_empty() const { return sizeof(buffer) == 0; }
    void free() { delete [] buffer; }
};

int main()
{
    IntComparator compare = IntComparator();
    /*int *buffer = new int[10];
    for(int i = 0; i < 10; i++)
    {
        buffer[i] = 10 - i;
    }
    std::cout << "sth";
    quick_sort<int>(compare, buffer, 0, 9);
    for(int i = 0; i < 10; i++)
    {
        std::cout << buffer[i] << " ";
    }*/
    PriorityQueue<int> queue(compare);
    if(queue.is_empty()) 
    {
        std::cout << "Queue is empty...\n";
    }
    for(int i = 0; i < 10; i++)
    {
        queue.push(i + 1);
        queue.print();
    }
    queue.poll();
    queue.print();
    std::cout << queue.peek() << "\n";
    return 0;
}
