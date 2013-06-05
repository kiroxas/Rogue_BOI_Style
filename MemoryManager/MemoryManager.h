#include <cstdlib>
#include <iostream>
#include <map>
#include <new>
#include <exception>
#include <set>

class StackAllocator
{
public :
	typedef unsigned int Marker;

	explicit StackAllocator(unsigned int);
	~StackAllocator();

	void* alloc(unsigned int);
	void* allocAligned(unsigned int, unsigned int);
	void freeToMarker(Marker);
	void clear();
	Marker getMarker();

private:
	char* ptr;
	unsigned int size;
	unsigned int total_size;
};

class NormalAllocator
{
public :
	explicit NormalAllocator(unsigned int);

	void* alloc(unsigned int);
	void free(void* to_delete);
private :
	char* ptr;
	std::map<unsigned int,std::set<char*> > manager;
	std::map<char*, unsigned int> allocated;
};

void* operator new(size_t size);
void* operator new(size_t size, unsigned int align);
void operator delete (void* mem);
void* operator new[](size_t size);
void operator delete[](void* mem);
