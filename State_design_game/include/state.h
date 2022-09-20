
class Player;

class State
{
    public:
        State(Player* owner);
        virtual ~State();
        virtual void Step() = 0;
    
    protected:
        Player* Owner;

};