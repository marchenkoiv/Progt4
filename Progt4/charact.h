/*#ifndef _charact_
#define _charact_

#include <iostream>
#include "board.h"


namespace Prog4
{
	class charact
	{
	private:
		std::string name;
		int maxhealth;
		int health;
		int gold;
	public:
		charact() : name(""), maxhealth(0), health(0), gold(0) {}
		charact(std::string, int, int, int);
		friend class enemy;
		friend class castle;
		void reducehealth(int a) { health -= a; }
		void setname(std::string a) { name = a; }
		void sethealth(int a) { maxhealth = a; health = a; }
		void addgold(int a) { gold += a; }
	};
}
#endif*/