#ifndef  FINAL_STATE_H
#define  FINAL_STATE_H

#include "Emergency.h"
#include "State.h"

class Accept_State : public State{

public:
	virtual ~Accept_State(){}

	Accept_State(const std::string & seq_name) : State(1), seq_name(seq_name){}

	virtual  State::id_type			handle_event(const Event& ev)const	{ throw Emergency(seq_name, ev); }
	static	Accept_State*			createEmpty()						{ return new Accept_State; }
	virtual void					serialize(Archive& stream);

private:
	Accept_State() :State(1){}
	std::string seq_name;
};

#endif