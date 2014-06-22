
#ifndef  PERSIST_H
#define PERSIST_H

#include <string>
#include <vector>

/*
a class that represents some device that supports read/write (for example a file)
*/

class Archive
{
public:
	Archive(bool isStoring = true) : _isStoring(isStoring) {}
	virtual ~Archive() {}

	virtual void write(const void* buffer, size_t length) {}
	virtual void read(void* buffer, size_t length) {}

	Archive& operator<<(const std::string& str);
	Archive& operator>>(std::string& str);

	Archive& operator<<(int val);
	Archive& operator>>(int& val);

	/*
	add more if needed
	*/

	bool isStoring() const				{ return _isStoring; }
	void setDirection(bool isStoring)	{ _isStoring = isStoring; }

private:
	bool _isStoring;
};


class ArchiveFile : public Archive
{
public:
	ArchiveFile(std::iostream* stream) : stream(stream) {}
	virtual ~ArchiveFile() {}

	virtual void write(const void *buffer, size_t length);
	virtual void read(void* buffer, size_t length);

private:
	std::iostream* stream;
};


/*
saves data to a vector <char>
*/
class ArchiveRaw : public Archive
{
public:
	virtual void		write(const void *buffer, size_t length)	
	{ 
		int i = 0; 
		while (length--) data.push_back(*  (((char*)buffer)+ (i++  ))  ); 
	}
	std::vector<char>	get_raw() const								{ return data; }
	const int			getSize()const								{ return data.size(); }
	virtual void		read(void* buffer, size_t length)			{ /*not implemented for now */ }

private:
	int from;
	std::vector<char> data;

};


class Persistent
{
public:
	virtual ~Persistent() {}

	static Persistent*	load(Archive& stream);
	void				store(Archive& stream) const;

protected:
	virtual void		serialize(Archive& stream) = 0;

private:
	static Persistent*	Factory(const std::string className);
};



#endif