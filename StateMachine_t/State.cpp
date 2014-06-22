#include "State.h"

using namespace  std;

void State::serialize(Archive& stream) {
	if (stream.isStoring())
	{
		stream << state_id << accepting;
	}
	else
	{
		id_type id;
		stream >> id;
		*(const_cast<State::id_type *>(&state_id)) = id;

		int _accepting;
		stream >> _accepting;
		*(const_cast<State::id_type *>(&accepting)) = _accepting;

	}
}