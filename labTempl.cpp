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
    T pivot = buffer[right];
    int pivot_idx = left;
    for(int idx = left; idx < right; idx++)
    {
        if(compare(buffer[idx], pivot))
        {
            std::swap(buffer[idx], buffer[pivot_idx]);
            pivot_idx++;
        }
    }
    std::swap(buffer[pivot_idx], buffer[right]);
    return pivot_idx;
}

template<typename T>
void quick_sort(Comparator<T> &compare, T *buffer, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = partition_by_number(compare, buffer, left, right);
    quick_sort(compare, buffer, left, pivot - 1);
    quick_sort(compare, buffer, pivot + 1, right);
}

template<typename T>
class PriorityQueue
{
private:
    size_t buffer_size;
    T *buffer;
    Comparator<T> &compare;
public:
    PriorityQueue(Comparator<T> &compare): 
        buffer_size(0), buffer(new T[0]), compare(compare) {}
    void push(T value)
    {
        T *temp = new T[buffer_size + 1];
        for(size_t pos = 0; pos < buffer_size; pos++)
        {
            temp[pos] = buffer[pos];
        }
        temp[buffer_size] = value;
        size_t pos = buffer_size;
        while(pos > 0 && 
            compare(temp[(pos - 1) / 2], temp[pos]))
        {
            std::swap(temp[(pos - 1) / 2], temp[pos]);
            pos = (pos - 1) / 2;
        }
        delete [] buffer;
        buffer = temp;
        buffer_size++;
    }
    void heapify()
    {
        int idx = 0, left = 1, right = 2,
            largest = 0;
        
        while(true)
        {
            if(left < buffer_size && 
                compare(buffer[largest], buffer[left]))
            {
                largest = left;
            }
            if(right < buffer_size &&
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
        std::swap(buffer[0], buffer[buffer_size - 1]);
        T *temp = new T[buffer_size - 1];
        for(size_t pos; pos < buffer_size - 1; pos++)
        {
            temp[pos] = buffer[pos];
        }
        delete [] buffer;
        buffer = temp;
        buffer_size--;
        heapify();
    }
    void print() const
    {
        for(size_t pos = 0; pos < buffer_size; pos++)
        {
            std::cout << buffer[pos] << " ";
        }
        std::cout << "\n";
    }
    T peek() const { return buffer[0]; }
    bool is_empty() const { return buffer_size == 0; }
    void free() 
    { 
        delete [] buffer; 
        buffer_size = 0;
    }
};

int main()
{
    IntComparator compare = IntComparator();
    int *buffer = new int[10];
    for(int i = 0; i < 10; i++)
    {
        buffer[i] = 10 - i;
    }
    quick_sort<int>(compare, buffer, 0, 9);
    for(int i = 0; i < 10; i++)
    {
        std::cout << buffer[i] << " ";
    }
<<<<<<< HEAD
    std::cout << "\n";
=======
>>>>>>> db1b090a46d41a9e81f0544fce964f2899084382
    PriorityQueue<int> queue(compare);
    if(queue.is_empty()) 
    {
        std::cout << "Queue is empty...\n";
    }
    for(int i = 0; i < 10; i++)
    {
        queue.push(i + 1);
    }
    queue.poll();
    std::cout << queue.peek() << "\n";
    queue.print();
    return 0;
}
