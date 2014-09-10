#include "Suscribable.h"

UniversalPointer createHeartBeat()
{
	return CreateEmptyPtr([](void*){});
}

SubjectBase::SubjectBase() : heartBeat_(createHeartBeat()){}

Registration SubjectBase::registerObserver(UniversalPointer ptr)
{
	observers.push_back(ptr);
	std::weak_ptr<UniversalPointer::element_type> weakHeartBeat(heartBeat_);

	return CreateEmptyPtr([ptr,weakHeartBeat,this](void*)
	{
		if(auto isBeating = weakHeartBeat.lock())
		{
			observers.erase(std::remove(std::begin(observers), std::end(observers), ptr),
								std::end(observers));
		}
	});
}