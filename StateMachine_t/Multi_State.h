#ifndef MULTI_STATE_H
#define MULTI_STATE_H

#include "Mid_State.h"

class Multi_State :public Mid_State{

public:
	virtual ~Multi_State(){}

	Multi_State(int numOfLoops, Event::Event_Type looping_event_type) :
		looping_on_type(looping_event_type), loops_left(numOfLoops){}

	virtual  State::id_type			handle_event(const Event& ev)const;
	virtual void					serialize(Archive& stream);
	static	Multi_State*			createEmpty()				{ return new Multi_State; }

private:
	Multi_State() :Mid_State(){ }

	Event::Event_Type				looping_on_type;
	mutable int						loops_left;				//changed by handle_event()

};

#endif