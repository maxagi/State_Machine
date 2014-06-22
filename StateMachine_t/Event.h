#ifndef  EVENT_H
#define  EVENT_H
#include <ostream>




class Event{

public:
	virtual ~Event(){}
	typedef int id_type;

 	enum Event_Type		{ EV_ANY, EV_A, EV_B, EV_C };

	id_type				getId()		const			{ return id; }
	Event_Type			getType()	const			{ return type; }

protected:
	Event(const id_type& _id, const Event_Type& type) :id(_id), type(type){}

private:
	const id_type		id;
	const Event_Type	type;
};



//////////////////////////////////////////////////////////////////////////

/*for now every Event will have some default id value */

class Event_A : public Event{
public:
	~Event_A(){}
	Event_A(const id_type & id=1) :Event(id, Event_Type(1)){}
};




class Event_B : public Event{
public:
	~Event_B(){}
	Event_B(const id_type & id = 2) :Event(id, Event_Type(2)){}
};




class Event_C : public Event{
public:
	~Event_C(){}
	Event_C(const id_type & id = 3) :Event(id, Event_Type(3)){}
};

#endif