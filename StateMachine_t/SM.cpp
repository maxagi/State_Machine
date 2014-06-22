#include "SM.h"

SM::~SM()	
{
	CloseHandle(hMapFile);
	CloseHandle(CAN_WRITE);
	CloseHandle(CAN_READ);
	UnmapViewOfFile(pBuf);
}

void SM::write(const void* const data, const int len)
{
	WaitForSingleObject(CAN_WRITE, INFINITE);
	printf(TEXT("recieved CAN_WRITE signal! \n"));
	memcpy((void*)pBuf, data, len);
	if (!SetEvent(CAN_READ)) throw"cant signal CAN READ ! \n";
}

const void*const SM::read()const
{

	if (!SetEvent(CAN_WRITE)) throw"cant signal CAN READ ! \n";
	WaitForSingleObject(CAN_WRITE, INFINITE);
	printf(TEXT("recieved CAN_READ signal! \n"));
	return pBuf;
}


void SM::init()
{
	/****init hMapFile*****/
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		size,					// maximum object size (low-order DWORD)
		name.c_str());          // name of mapping object

	if (hMapFile == NULL) throw "X";


	/****init hMapFile*****/
	pBuf = (LPTSTR)MapViewOfFile(
		hMapFile,				// handle to map object
		FILE_MAP_ALL_ACCESS,	// read/write permission
		0,
		0,
		size);

	if (pBuf == NULL)
	{
		CloseHandle(hMapFile);
		return throw "X";

	}
	memset(pBuf, 0, size);

	/****init events*****/
	CAN_READ = CreateEvent(
		NULL,               // default security attributes
		FALSE,              // auto-reset event
		FALSE,              // initial state is non signaled
		TEXT("CAN_READ")	// object name
		);
	CAN_WRITE = CreateEvent(
		NULL,               // default security attributes
		FALSE,              // auto-reset event
		FALSE,              // initial state is non signaled
		TEXT("CAN_WRITE")	// object name
		);
}