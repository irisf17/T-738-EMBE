#include <stdint.h> //to import for uint

class Timer_msec
{
    public:
        Timer_msec();
        void init(int);
        void init(int period, float duty_cycle);
        void set(float duty_cycle);
};