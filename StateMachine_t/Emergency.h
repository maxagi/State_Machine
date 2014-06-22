#ifndef DANGER_H
#define  DANGER_H

#include "Event.h"
#include <iostream>
#include <string>

/*
thrown by Machine if an accepting state is reached. (that means its an emergency right? :P)
*/
struct Emergency
{
	Emergency(const std::string desc, const Event ev) :desc(desc), last_event(ev){}
	std::string desc;
	Event last_event;
};


/*
implementation of handling different 'Danger' cases
*/
class EmergencyHandler{
public:
	static void handle(const Emergency& danger){

		std::string danger_desc = danger.desc;

		if (danger_desc == "Seq1")
			std::cout << danger_desc;
		else if (danger_desc == "Seq2")
			std::cout << danger_desc;
		if (danger_desc == "Seq3")
			std::cout << danger_desc << ":[id " << danger.last_event.getId()
			<< ", type " << danger.last_event.getType() << "]";
	}
};

#endif