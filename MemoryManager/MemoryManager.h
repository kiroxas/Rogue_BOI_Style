#include <cstdlib>
#include <iostream>

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

StackAllocator s(2000);

void* operator new(size_t size)
{
	//std::cout << "In custom new for "<< size << std::endl;
    return s.alloc(size * sizeof(char));
}

void* operator new(size_t size, unsigned int align)
{
	//std::cout << "In custom new for "<< size << std::endl;
    return s.allocAligned(size * sizeof(char), align);
}

void operator delete (void* mem)
{
	std::cout << "Deleting "<< mem << std::endl;
   // free(mem);
}

// Don’t forget the array version of new/delete
void* operator new[](size_t size)
{
	std::cout << "In custom new[] for "<< size << std::endl;
   return s.alloc(size * sizeof(char));
}

void operator delete[](void* mem)
{
   // free(mem);
}

StackAllocator::~StackAllocator()
{
	clear();
	free(ptr);
}

StackAllocator::Marker StackAllocator::getMarker()
{
	return size;
}

void StackAllocator::freeToMarker(Marker m)
{
	Marker r = size -  m;

	if(r > 0)
		ptr -= r;

	size = m;
}

StackAllocator::StackAllocator(unsigned int t_size) :
	size(0),
	total_size(t_size)
{
	ptr = (char*)malloc(t_size * sizeof(char));
}

void* StackAllocator::alloc(unsigned int size_)
{
	std::cout << "In stackAllocator with size " << size << " on " << total_size << " and allocating : " << size_ << std::endl;
	if(size + size_ > total_size)
		return nullptr;

	void *tmp = ptr;
	ptr += size_;
	size += size_;

	return (void*)tmp;
}

void* StackAllocator::allocAligned(unsigned int size_, unsigned int align)
{
	unsigned int expanded_size = size_ + align;

	unsigned int rawAdress = (unsigned int)alloc(expanded_size);
	unsigned int mask = align - 1;
	unsigned int misalign = (rawAdress & mask);
	unsigned int adjust = align - misalign;
	unsigned int alignedAdress = rawAdress + adjust;
	unsigned int* padjust = (unsigned int *)(alignedAdress - 4);

	*padjust = adjust;

	return (void*)alignedAdress;
}

void StackAllocator::clear()
{
	ptr -= size;
}
