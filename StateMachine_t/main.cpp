/*
******************
written By Max Agi
******************
*/

#include "SM.h"
#include "Machine.h"
#include "Multi_State.h"

#include <iostream>
#include <fstream>
#include <iostream>

using namespace  std;

int main()
{






	/*

	building a machine to receive the following Event sequences:
	A,A,B,C,A
	A,B,C*1000,A
	A,C,<ANY>

	*/

	//prepare the states
	Mid_State* s1 = new Mid_State();
	Mid_State* s2 = new Mid_State();
	Mid_State* s3 = new Mid_State();
	Mid_State* s4 = new Mid_State();
	Mid_State* s5 = new Mid_State();

	Multi_State* s6 = new Multi_State(2, Event::EV_A);
	Mid_State* s7 = new Mid_State();

	Accept_State *s8 = new Accept_State("Seq1");
	Accept_State *s9 = new Accept_State("Seq2");
	Accept_State *s10 = new Accept_State("Seq3");


	//configure transitions
	s1->add_transition(Event::EV_A, s2);
	s2->add_transition(Event::EV_A, s3);
	s2->add_transition(Event::EV_B, s6);
	s2->add_transition(Event::EV_C, s7);
	s3->add_transition(Event::EV_B, s4);
	s4->add_transition(Event::EV_C, s5);
	s5->add_transition(Event::EV_B, s8);
	s6->add_transition(Event::EV_A, s9);
	s7->add_transition(Event::EV_ANY, s10);


	//put all states in a list
	Machine::states_list states;
	states.push_back(s1);
	states.push_back(s2);
	states.push_back(s3);
	states.push_back(s4);
	states.push_back(s5);
	states.push_back(s6);
	states.push_back(s7);
	states.push_back(s8);
	states.push_back(s9);
	states.push_back(s10);


	//initialize stuff for saving and loading the machine later
	fstream file("m1.machine", ios::out | ios::in | ios::binary | ios::trunc);
	ArchiveFile stream(&file);
	//save state to file


	Machine* m2 = 0;


	//initialize and run Machine
	Machine m1(s1, states);
// 	m1.save_machine_state(stream);




	/*
	try
	{	//an example with the A,A,B,C,A sequence:

	m1.recieve_event(Event_A());
	m1.recieve_event(Event_A());
	m1.recieve_event(Event_B());


	//save state to file
	m1.save_machine_state(stream);

	//load state from  file to a new machine object
	file.seekg(0, ios::beg);
	m2 = Machine::load_machine_state(stream);


	//continue execution with loaded machine
	m2->recieve_event(Event_C());
	m2->recieve_event(Event_A());
	}

	catch (Emergency e)
	{
	EmergencyHandler::handle(e);
	}


	catch (const char * error_msg)
	{
	cout << error_msg;
	}
	*/

	//look you can also get the raw data as a vector<char> :
	ArchiveRaw aRaw;
	m1.save_machine_state(aRaw);
	vector<char> raw = aRaw.get_raw();

	//raw now contains the machine data. you can use it for many things :) 

	SM sm("Machine_SM",1024);
	char * sendBuf = (char*)&raw[0];
	sm.write(sendBuf, 372);



	file.close();
	delete m2;


	//hold to see result
	int x; cin >> x;
}