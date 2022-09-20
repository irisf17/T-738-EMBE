class Timer0
{
public:
    Timer0();
    void init(int period_msec);
    void init(int period_msec, float duty_cycle);
    void set(float duty_cycle);
};