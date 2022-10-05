#include <iostream>
#include <random>

using State = int;

class ArbitraryState 
{
public:
    virtual bool contains(State s) const = 0; 
};

class DiscreteState: public ArbitraryState
{
private:
    State const s0;
public:
    DiscreteState(State s0): ArbitraryState(), s0(s0) { }
    bool contains(State s) const override
    {
        return s == s0;
    }
};

class SegmentState: public ArbitraryState 
{
private:
    State const begin_s0, end_s0;
public:
    SegmentState(State begin_s0, State end_s0):
        ArbitraryState(), begin_s0(begin_s0), end_s0(end_s0) { }
    bool contains(State s) const override 
    {
        return begin_s0 <= s and end_s0 >= s;
    }
};

class ProbabilityTest 
{
private:
    State const E_min, E_max;
public:
    ProbabilityTest(State E_min, State E_max): 
        E_min(E_min), E_max(E_max) { }
    float test(
        ArbitraryState &system,
        unsigned test_count,
        unsigned seed) const 
    {
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt) 
        {
            if (system.contains(dstr(reng))) ++good;
        }
        return
            static_cast<float>(good)
            /static_cast<float>(test_count);
    }
};

int main() 
{
    DiscreteState d(0);
    SegmentState s(0, 100);
    ProbabilityTest pt(-1000, 1000);
    std::cout << pt.test(d, 20000, 1) << std::endl;
    std::cout << pt.test(s, 20000, 1) << std::endl;
    return 0;
}
