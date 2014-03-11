#include "MemoryManager.h"

StackAllocator s(2000);
NormalAllocator n(5000);

NormalAllocator::NormalAllocator(unsigned int t_size)
{
	ptr = (char*)malloc(t_size * sizeof(char));

	if(!ptr) throw std::bad_alloc();

	manager[t_size].insert(ptr);
}

void* NormalAllocator::alloc(unsigned int t_size)
{
	char * ret = nullptr;

	for(auto e : manager)
	{
		if(e.first > t_size)
		{
			ret = *e.second.begin();
			allocated[ret] = t_size;

			manager[e.first - t_size].insert(ret + t_size); // Let's "reallocate" the smaller chunk
			e.second.erase(ret); // We gave that, let's delete this one

			if(e.second.empty())
				manager.erase(e.first); // If we do not have a chunk of memory of this size, let's delete

			break;
		}
		else if (e.first == t_size)
		{
			ret = *e.second.begin();
			allocated[ret] = t_size;

			e.second.erase(ret);

			if(e.second.empty())
				manager.erase(e.first); // If we do not have a chunk of memory of this size, let's delete

			break;
		}
	}

	infos();
	if(!ret) throw std::bad_alloc();
	return ret;
}

void NormalAllocator::free(void* to_delete)
{
	char* to_del = static_cast<char*>(to_delete);
	//ok, let's make it reallocable
	 //is it a pointer allocated here ?
	if(allocated.find(to_del) == allocated.end());
		return;

	 //first what's it's size ?
	const unsigned int size = allocated[to_del];
	allocated.erase(to_del);

	for(auto e : manager)
	{
		for(auto c : e.second)
		{
			if(c + e.first == to_del) // First case, the memory we are freeing is after this one, let's allocate a bigger chunk
			{
				manager[e.first + size].insert(c);
				e.second.erase(c);

				if(e.second.empty())
					manager.erase(e.first);
				return;
			}
			else if(to_del + size == c) // Second case,  the memory we are freeing is followed by this one, let's allocate a bigger chunk
			{
				manager[e.first + size].insert(to_del);
				e.second.erase(c);

				if(e.second.empty())
					manager.erase(e.first);
				return;
			}
		}
	}

	//Can't allocate a bigger chunk, let's just reaalocate the small one then.
	manager[size].insert(to_del);
	infos();
}

void NormalAllocator::infos() const
{
	std::cerr << "Manager :" << std::endl;
	for(auto e : manager)
	{
		std::cerr << "- " << e.first << ": ";
		for(auto c : e.second)
			std::cerr << &c << " " ;
		std::cerr << std::endl;
	}
	std::cerr << "Allocated :" << std::endl;
	for(auto e : allocated)
	{
		std::cerr << "- " << &(e.first) << ":" << e.second << std::endl;
	}
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
	if(!ptr) throw std::bad_alloc();
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


void* operator new(size_t size)
{
    return n.alloc(size * sizeof(char));
}

void* operator new(size_t size, unsigned int align)
{
    return s.allocAligned(size * sizeof(char), align);
}

void operator delete (void* mem)
{
	std::cout << "Deleting "<< mem << std::endl;
	n.free(mem);
}

// Don’t forget the array version of new/delete
void* operator new[](size_t size)
{
	std::cout << "In custom new[] for "<< size << std::endl;
    return n.alloc(size * sizeof(char));
}

void operator delete[](void* mem)
{
	n.free(mem);
}
