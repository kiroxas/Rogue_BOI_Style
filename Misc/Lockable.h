#ifndef LOCKABLE_H
#define LOCKABLE_H

class Lockable
{
	public :

	virtual void Lock(){locked = true;}
	virtual void Unlock(){locked = false;}
	virtual bool isLocked() const {return locked;}

	private :

	bool locked = true;

};

#endif