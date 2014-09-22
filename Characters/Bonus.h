#ifndef BONUS_H
#define BONUS_H

class Hittable;

class Bonus
{
public :
	using type = unsigned long long;

	Bonus(type h = 0, type m_h = 0, type a = 0);

	void applyTo(Hittable*) const;

private :
	type max_health;
	type health;
	type attack;
};

#endif
