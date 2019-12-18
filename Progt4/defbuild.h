#ifndef _defbuild_
#define _defbuild_
#include <iostream>
#include <map>
#include <vector>
#include "point.h"
using std::string;
using std::map;
using std::vector;
//#include"mymap.h"
//#include "myvec.h"


namespace Prog4
{
	class enemy;
	class castle;
	



	class magic
	{
	private:
		unsigned int slowdown;
		unsigned int poison;
		unsigned int weaking;
	public:
		magic(int a = 0, int b = 0, int c = 0) : slowdown(a), poison(b), weaking(c) {};
		friend  magic operator +(const magic& s, const magic& s1);
		friend class enemy;
		int getsl() { return slowdown; };
		int getpo() { return poison; };
		int getwe() { return weaking; };
		magic operator += (const magic&);
	};


	class towlevel
	{
	protected:
		unsigned int cost;
		unsigned int rad;
	public:
		void setcost(int a = 0) { cost = a; }
		void setrad(int a = 0) { rad = a; }
		virtual towlevel & operator = (const towlevel& ob);
		virtual map<int, towlevel*> setset(int a) = 0;
		virtual magic geteff() = 0;
		virtual int getdamage() = 0;
		virtual int getrate() = 0;
		friend class enemy;
		friend class castle;
		friend class defbuilding;
	};


	class magictrap : virtual public towlevel
	{
	protected:
		magic eff;
	public:
		magictrap(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0 ) :  eff(a, b, c) { setcost(d); setrad(e); };
		magictrap(const magictrap& a) { eff = a.eff; }
		virtual map<int, towlevel*> setset(int a);
		virtual magictrap & operator = (const magictrap& ob);
		virtual  magic geteff() { return eff; };
		virtual int getdamage() { return 0; };
		virtual int getrate() { return 0; };
		friend class defbuilding;
		friend class enemy;
		friend class board;
	};

	class tower : virtual public towlevel
	{
	protected:
		unsigned int damage;
		unsigned int rate;
	public:
		tower(int a = 0, int b = 0, int d = 0, int e = 0) : damage(a), rate(b) { setcost(d); setrad(e); };
		virtual map<int, towlevel*> setset(int a);
		virtual tower & operator = (const tower& ob);
		virtual  magic geteff() { return 0; };
		virtual int getdamage() { return damage; };
		virtual int getrate() { return rate; };
		friend class magictower;
		friend class defbuilding;
		friend class castle;
		friend class board;
	};

	class magictower : public magictrap, public tower
	{
	public:
		magictower() : magictrap(), tower() {};
		magictower( magictrap b, tower c, int d = 0, int e = 0) : magictrap(b), tower(c) { setcost(d); setrad(e); };
		virtual  magic geteff() { return eff; };
		virtual int getdamage() { return damage; };
		virtual int getrate() { return rate; };
		virtual magictower & operator = (const magictower& ob);

		virtual map<int, towlevel*> setset(int a);
		friend class board;
	};


	class defbuilding
	{
	private:
		point coord;
		int level;
	    typedef map <int, towlevel *> levchar;
		levchar lev;
		int time;
	public:
		friend class enemy;
		friend class castle;
		friend class board;
		friend class towlevel;
		defbuilding(int a = 0, int b = 0) : coord(a, b), level(1), time(1) {};
		defbuilding(point a) : coord(a), level(0), time(1) {};
		~defbuilding() {};
		void lvlup() { level++; };
		point getcoord() { return coord; }
		int getx() { return coord.getx(); }
		int gety() { return coord.gety(); }
		int getlevel() { return level; }
		int shot(vector<enemy>, castle);
		void setcoord(point p) { coord = p; };
		void setlevels(int a, towlevel *t) { lev = (t->setset(a)); };
		int getrate(){ return lev[level]->getrate(); };
		void settime(int t) { time += t; }
		int gettime() { return time; }
	};

	/*template<class T> using magt = map<int, T>; // ИД-типа является vector<T, Alloc<T>>
	magt<magictower> v;*/

}
#endif