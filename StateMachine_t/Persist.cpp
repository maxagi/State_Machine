#include "Accept_State.h"
#include "Mid_State.h"
#include "Multi_State.h"

#include "Persist.h"
#include <vector>
#include "Machine.h"
using namespace  std;

Archive& Archive::operator<<(int val)
{
	write(&val, sizeof(int));
	return *this;
}

Archive& Archive::operator>>(int& val)
{
	read(&val, sizeof(int));
	return *this;
}

Archive& Archive::operator<<(const string& str)
{
	int length = str.length();
	*this << length;
	write(str.c_str(), sizeof(char)* length);
	return *this;
}

Archive& Archive::operator>>(string& str)
{
	int length = -1;
	*this >> length;
	vector<char> mem(length + 1);
	char* pChars = &mem[0];
	read(pChars, sizeof(char)* length);
	mem[length] = NULL;
	str = pChars;
	return *this;
}


void ArchiveFile::write(const void* buffer, size_t length)
{
	stream->write((const char*)buffer, length);
	if (!*stream)
		throw "ArchiveFile::write Error";
}

void ArchiveFile::read(void* buffer, size_t length)
{
	stream->read((char*)buffer, length);
	if (!*stream)
		throw "ArchiveFile::read Error";
}



void Persistent::store(Archive& stream) const
{
	string className = typeid(*this).name();

	className = className.substr(className.find(' ') + 1);

	stream << className;

	stream.setDirection(true);

	const_cast<Persistent *>(this)->serialize(stream);
}



Persistent* Persistent::load(Archive& stream)
{
	string className;
	stream >> className;

	Persistent *obj =Factory(className);
	auto_ptr<Persistent> ob_ptr(obj);

	stream.setDirection(false);

	obj->serialize(stream);

	ob_ptr.release();
	return obj;

}

Persistent*	Persistent::Factory(const std::string className)
{
	Persistent *result = 0;
	if (className == "Machine")
		result = Machine::createEmpty();
	else if (className == "Mid_State")
		result = Mid_State::createEmpty();
	else if (className == "Accept_State")
		result = Accept_State::createEmpty();
	else if (className == "Multi_State")
		result = Multi_State::createEmpty();
	return result;
}
