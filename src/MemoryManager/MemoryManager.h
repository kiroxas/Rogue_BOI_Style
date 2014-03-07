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

template <class T>
class MyCustomAlloc
{
public:
    typedef T          value_type;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
 
    typedef T*         pointer;
    typedef const T*   const_pointer;
 
    typedef T&         reference;
    typedef const T&   const_reference;
 
    MyCustomAlloc()
    {}

private:
    void operator =(const MyCustomAlloc &);
public:

    ~MyCustomAlloc()
    {
    }
 
    template <class U>
    struct rebind
    {
        typedef MyCustomAlloc<U> other ;
    };

	template <class _Other>
    MyCustomAlloc(const MyCustomAlloc<_Other> &other)
    {
    }
 
 
    pointer
    address( reference r ) const
    {
        return &r;
    }
 
    const_pointer
    address( const_reference r ) const
    {
        return &r;
    }
 
    pointer
    allocate( size_type n, const void* /*hint*/=0 )
    {
        return (pointer)malloc(n*sizeof(T));
    }
 
    void
    deallocate( pointer p, size_type /*n*/ )
    {
            free( p);
    }
 
    void
    construct( pointer p, const T& val )
    {
        new ((void*)p) T(val);
    }
 
    void
    destroy( pointer p )
    {
        p->~T();
    }
 
    size_type
    max_size() const
    {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

 
};

class NormalAllocator
{
public :
	typedef std::set<char*, std::less<char*>, MyCustomAlloc<char>> my_set;
	typedef std::map<char*, unsigned int, std::less<char*>, MyCustomAlloc<unsigned int>> allocating_container;
	typedef std::map<unsigned int, my_set, std::less<unsigned int>, MyCustomAlloc<my_set>> manager_container;

	explicit NormalAllocator(unsigned int);

	void* alloc(unsigned int);
	void free(void* to_delete);
private :

	void infos() const;

	char* ptr;
	manager_container manager;
	allocating_container allocated;
	my_set n;
};

void* operator new(size_t size);
void* operator new(size_t size, unsigned int align);
void operator delete (void* mem);
void* operator new[](size_t size);
void operator delete[](void* mem);
 
 
template <class T, class T1>
bool
operator==( const MyCustomAlloc<T>& left, const MyCustomAlloc<T1>& right )
{
	return true;
}
 
template <class T, class T1>
bool
operator!=( const MyCustomAlloc<T>& left, const MyCustomAlloc<T1>& right)
{
    return false;
}
