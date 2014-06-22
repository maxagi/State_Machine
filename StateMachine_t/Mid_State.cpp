#include "Mid_State.h"

using namespace std;


void Mid_State::add_transition(const  Event::Event_Type& eventType, const State* const toState)
{
	transitions.insert(make_pair(eventType, toState->getId()));
}



State::id_type Mid_State::handle_event(const Event& ev)const
{
	transition_table::const_iterator found;

// 	if ((found = transitions.find(Event::EV_ANY)) != transitions.cend())  /* can also be implemented by operator== of some Event_Type class */
// 		return found->second;

	if (ev.getType() == 4)
		return found->second;

	found = transitions.find(ev.getType());
	if (found == transitions.cend())
		throw "Machine is Stuck";
	return found->second;
}


void	Mid_State::serialize(Archive& stream)
{
	if (stream.isStoring())
	{
		stream << transitions.size();

		for (transition_table::const_iterator transition = transitions.cbegin(); transition != transitions.cend(); ++transition)
		{
			stream << transition->first; //Event_Type
			stream << transition->second;
		}
	}

	else
	{
		int tbl_size;
		stream >> tbl_size;

		while (tbl_size--)
		{
			int et;
			State::id_type sid;
			stream >> et;
			stream >> sid;
			transitions.insert(std::make_pair((Event::Event_Type)et, sid));
		}
	}

	//continue with base serialization
	State::serialize(stream);
}


