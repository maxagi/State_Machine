#include "Multi_State.h"


State::id_type Multi_State::handle_event(const Event& ev)const
{
	if (loops_left)
	{
		if (ev.getType() == looping_on_type)
		{
			--loops_left;
			return this->getId();
		}
		else throw "Machine is Stuck";
	}
	else
	{
		return Mid_State::handle_event(ev);
	}
}

void Multi_State::serialize(Archive& stream)
{
	if (stream.isStoring())
	{
		stream << looping_on_type << loops_left;
	}
	else
	{
		int et,step;

		stream >> et>>step;

		looping_on_type = Event::Event_Type(et);
		loops_left = step;
	}
	Mid_State::serialize(stream);
}


