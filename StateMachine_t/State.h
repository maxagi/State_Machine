#ifndef  STATE_H
#define  STATE_H

#include "Persist.h"
#include "Event.h"

class State :public Persistent{
public:
	virtual ~State(){}

	typedef int	id_type;
	virtual		id_type		handle_event(const Event& ev)const = 0;

	id_type					getId()const		{ return state_id; }
	int 					isAccpeting()const	{ return accepting; }

	virtual void			serialize(Archive& stream);

protected:
	State(const int  isAccepting) :state_id(nextId()), accepting(isAccepting){}

private:
	id_type nextId()	{ static id_type next_id = 0; return ++next_id; }

	const id_type	state_id;
	const int		accepting;
};

#endif