#include <Arduino.h>

class Context;

class State
{

protected:
	Context *context_;

public:
	virtual ~State()
	{
	}

	void set_context(Context *context)
	{
		this->context_ = context;
	}

	virtual void set() = 0;

	virtual void on_entry() = 0;

	virtual void set_pre() = 0;

	virtual void on_exit() = 0;

	virtual void on_stop() = 0;
	
	virtual void on_reset() = 0;
};

class Context
{
	/**
	 * @var State A reference to the current state of the Context.
	 */

private:
	State *state_;

public:
	Context(State *state) : state_(nullptr)
	{
		this->transition_to(state);
	}

	~Context()
	{
		delete state_;
	}

	/**
	 * The Context allows changing the State object at runtime.
	 */

	void transition_to(State *state)
	{
		if (this->state_ != nullptr)
		{
			this->state_->on_exit();
			delete this->state_;
		}

		this->state_ = state;

		this->state_->set_context(this);

		this->state_->on_entry();
	}

	/**
	 * The Context delegates part of its behavior to the current State object.
	 */

	void Trigger_state()
	{
		this->state_->set();
	}

	void Set_pre()
	{
		this->state_->set_pre();
	}	

	// void Go()
	// {
	// 	this->state_->on_go();
	// }

	void Stop()
	{
		this->state_->on_stop();
	}

	void Reset()
	{
		this->state_->on_reset();
	}
};

class Initialization : public State
{
public:
	void set() override{}

	void on_entry() override;

	void set_pre() override{}

	void on_exit() override{}

	void on_stop() override{}

	void on_reset() override{}
};

class Pre_Operational : public State
{
public:
	void set() override;

	void on_entry() override;

	// USE semicolom ; if function is used in .cpp file!
	void set_pre() override{}

	void on_exit() override {}

	void on_stop() override;

	void on_reset() override;
};

class Operational : public State
{
public:
	void set() override{}

	void on_entry() override;

	void set_pre() override;

	void on_exit() override{}

	void on_stop() override;

	void on_reset() override;
};

class Stop_state : public State
{
public:
	void set() override;

	void on_entry() override;

	void set_pre() override;

	void on_exit() override{}

	void on_stop( ) override;

	void on_reset() override;
};