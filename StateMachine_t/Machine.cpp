#include "Machine.h"
using namespace std;


Machine::Machine(const State* const start, const states_list& states) :
curent_state_id(start->getId())
{
	for (states_list::const_iterator state = states.cbegin(); state != states.cend(); ++state)
	{
		IdToState.insert(make_pair((*state)->getId(), *state));
	}
}


Machine::~Machine()
{
	for (StateIdMap::const_iterator id_to_state = IdToState.cbegin(); id_to_state != IdToState.cend(); ++id_to_state)
		delete id_to_state->second;
}


State*	Machine::findState(const State::id_type& id)const
{
	StateIdMap::const_iterator found_state = IdToState.find(id);
	if (found_state == IdToState.cend())
		throw "state id not found in Machine's state list ";
	return found_state->second;
}

void Machine::recieve_event(const  Event& ev)
{
	//get a pointer to the  current state
	State* prev_state = findState(curent_state_id);

	//calculate next state id 
	curent_state_id = prev_state->handle_event(ev);

	//get a pointer to the next state
	State* current_state = findState(curent_state_id);

	//if state is accepting , Accepting_State::handle_event will throw the relevant 'Danger' exception
	if (current_state->isAccpeting())
	{
		current_state->handle_event(ev);
	}
}



void Machine::serialize(Archive& stream)
{
	if (stream.isStoring())
	{
		//serialize states
		stream << IdToState.size();
		for (StateIdMap::const_iterator id_to_state = IdToState.cbegin(); id_to_state != IdToState.cend(); ++id_to_state)
			(id_to_state->second)->store(stream);

		//serialize current state:
		stream << curent_state_id;
	}

	else
	{
		//serialize states
		int states_size;
		stream >> states_size;

		while (states_size--)
		{
			State* s = dynamic_cast<State*>(Persistent::load(stream));
			IdToState.insert(std::make_pair(s->getId(), s));
		}

		//serialize current state:
		State::id_type id;
		stream >> id;
		curent_state_id = id;
	}
}