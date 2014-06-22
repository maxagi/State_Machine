#ifndef  MACHINE_H
#define  MACHINE_H

#include <list>
#include<map>

#include "Persist.h"
#include "Accept_State.h"


class Machine :public Persistent{ 

public:
	typedef  std::list <State*>		states_list;

	virtual ~Machine();
	Machine(const State* const start, const states_list& states);

	void				recieve_event(const  Event& ev);

	virtual void		serialize(Archive& stream);
	void				save_machine_state(Archive& stream) const	{ store(stream); }
	static	Machine*	load_machine_state(Archive& stream)			{ return dynamic_cast<Machine*>(load(stream)); }
	static	Machine*	createEmpty()								{ return new Machine; }

private:
	Machine() {}
	Machine(const Machine&);
	Machine& operator=(const Machine&);


	State*				findState(const State::id_type& id)const;

	typedef std::map<const State::id_type, State*const > StateIdMap;

	StateIdMap					IdToState;
	State::id_type				curent_state_id;
};


#endif