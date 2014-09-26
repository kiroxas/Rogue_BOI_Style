#ifndef BONUS_H
#define BONUS_H

struct Hittable;

class Bonus
{
public :
	using type = unsigned long long;

	Bonus(type h = 0, type m_h = 0, type a = 0);

	void applyTo(Hittable*) const;
	void clear();

private :
	type health;
	type max_health;
	type attack;
};

#endif
