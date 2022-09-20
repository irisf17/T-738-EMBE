#include <stdint.h>
#include <avr/io.h>

class Digital_out
{
    public:
        Digital_out(int pin); //pinMask is the bitmask for the registor
        void init();
        void set_hi();
        void set_lo();
        void toggle();
    private:
        uint8_t pinMask;
};