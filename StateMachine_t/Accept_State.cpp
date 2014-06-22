#include "Accept_State.h"

void  Accept_State::serialize(Archive& stream)
{
	if (stream.isStoring())
		stream << seq_name;
	else
		stream >> seq_name;

	State::serialize(stream);
}