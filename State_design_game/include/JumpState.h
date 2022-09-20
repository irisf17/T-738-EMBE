#include <state.h>

class JumpState : public State
{
    public:
        JumpState(Player* owner);
        virtual void Step() override;

    private:
        int CountDown;
};