#ifndef MID_STATE_H
#define MID_STATE_H

#include <map>
#include "State.h"


/*
a simple State implementation, holds a transition table 
and can return the state id of the next sate 
*/

class Mid_State : public State{

public:
	virtual ~Mid_State(){}
	Mid_State() :State(0){}

	void					add_transition(const Event::Event_Type& eventType, const State* const toState);
	virtual  id_type		handle_event(const Event& ev)const;

	virtual void			serialize(Archive& stream);
	static	Mid_State*		createEmpty()				{ return new Mid_State; }

private:
	typedef std::map<const  Event::Event_Type, const State::id_type >  transition_table;		//maps an event to the next state id.
	transition_table	transitions;

};

#endif