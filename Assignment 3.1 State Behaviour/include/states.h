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

	virtual void on_do() = 0;

	virtual void on_entry() = 0;

	virtual void on_exit() = 0;

	virtual void on_go() = 0;

	virtual void on_stop() = 0;
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

	void do_work()
	{
		this->state_->on_do();
	}

	void Go()
	{
		this->state_->on_go();
	}

	void Stop()
	{
		this->state_->on_stop();
	}
};

class Red : public State
{
public:
	void on_do() override{}

	void on_entry() override;

	void on_exit() override
	{
	}

	void on_go() override;

	void on_stop() override;
};

class Yellow : public State
{
public:
	void on_do() override {}

	void on_entry() override;

	void on_exit() override {}

	void on_go() override{}

	void on_stop() override{}
};

class Green : public State
{
public:
	void on_do() override
	{
	}

	void on_entry() override;

	void on_exit() override
	{
	}

	void on_go() override;

	void on_stop() override;
};