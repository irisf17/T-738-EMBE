#include <stdint.h>
#include <avr/io.h>

class Digital_in
{
public:
    Digital_in(int pin); // pinMask is the bitmask for the registor
    void init();
    bool is_hi();
    bool is_lo();

private:
    uint8_t pinMask;
};