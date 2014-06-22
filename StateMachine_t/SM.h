#ifndef  SM_H
#define SM_H


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <string>



class SM{

public:
	~SM();
	SM(const std::string& sm_name,const int size) :name(sm_name),size(size)	{ init(); }

	void				write(const void* const data, const int len);
	const void*const	read()const;
	void				init();

	std::string name;
	HANDLE		hMapFile;
	HANDLE		CAN_READ;
	HANDLE		CAN_WRITE;
	LPTSTR		pBuf;
	int			size;
};



#endif