#include <state.h>

class StandState : public State
{
    public:
        StandState(Player* owner);
        virtual void Step() override;
    
    private:
        int CountDown;
};