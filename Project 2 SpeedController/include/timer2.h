#include <stdint.h> //to import for uint

class Timer2
{
    public:
        Timer2();
        void init(int);
        void init(int period, float duty_cycle);
        void set(float duty_cycle);
};