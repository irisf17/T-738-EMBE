#include <stdint.h> //to import for uint

class Timer1
{
    public:
        Timer1();
        void init(int);
        void init(int period, float duty_cycle);
        void set(float duty_cycle);
};