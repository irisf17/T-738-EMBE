
class State;

class Player
{
    public:
        Player();
        void Step();

        template <typename T>
        void ChangeCurrentState();
    
    private:
        State* CurrentState;
};

template <typename T>
void Player::ChangeCurrentState()
{
    Serial.println("Change STATE Called");
    delete CurrentState;
    CurrentState = new T(this);
}