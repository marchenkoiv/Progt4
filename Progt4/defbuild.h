#ifndef _defbuild_
#define _defbuild_
#include <iostream>
#include <map>
#include <vector>
#include "point.h"
using std::string;
using std::map;
using std::vector;


namespace Prog4
{
	class enemy;

	template <typename T>
	class defbuilding
	{
	private:
		point coord;
		int level;
		typedef map <int, T> levchar;
		levchar lev;
	public:
		friend class enemy;
		friend class castle;
		friend class board;
		defbuilding<T>(int a=0, int b=0) : coord(a, b), level(1) {};
		defbuilding<T>(point a) : coord(a), level(0) {};
		~defbuilding<T>() {};
		void lvlup() { level++; };
		point getcoord() { return coord; }
		int getlevel() { return level; }
		int shot(vector<enemy>);
		void setlevels( int a);
	};


	class magic
	{
	private:
		unsigned int slowdown;
		unsigned int poison;
		unsigned int weaking;
	public:
		magic(int a = 0, int b = 0, int c = 0) : slowdown(a), poison(b), weaking(c) {};
		friend class enemy;
		magic operator += (const magic&);
	};


	class towlevel
	{
	private:
		unsigned int cost;
		unsigned int rad;
	public:
		towlevel(int a = 0, int b = 0) : cost(a), rad(b) {};
		towlevel &operator =(const towlevel &a) { cost = a.cost; rad = a.rad; return *this; }
		towlevel(const towlevel &a) { cost = a.cost; rad = a.rad; }
		friend class enemy;
		friend class castle;
	};


	class magictrap : virtual public towlevel
	{
	private:
		magic eff;
	public:
		magictrap() : towlevel(0, 0), eff(0,0,0) {};
		magictrap(const towlevel t, int a = 0, int b = 0, int c = 0) : towlevel(t), eff(a, b, c) {};
		magictrap(const magictrap& a) { eff = a.eff; }
		friend class defbuilding<magictrap>;
		friend class enemy;
		friend class board;
	};

	class tower : virtual public towlevel
	{
	private:
		unsigned int damage;
		unsigned int rate;
	public:
		tower(towlevel r, int a = 0, int b = 0) : damage(a), rate(b), towlevel(r) {};
		tower() :damage(0), rate(0), towlevel(0, 0) {};
		friend class magictower;
		friend class defbuilding<tower>;
		friend class castle;

		friend class board;
	};

	class magictower : public magictrap, public tower
	{
	public:
		magictower() : magictrap(), tower(), towlevel() {};
		magictower(const towlevel t, magictrap b, tower c) : magictrap(b), tower(c), towlevel(t) {};
		friend class board;
	};


	/*template<class T> using magt = map<int, T>; // ИД-типа является vector<T, Alloc<T>>
	magt<magictower> v;*/

}
#endif