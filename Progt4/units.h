
#ifndef _units_
#define _units_

#include <iostream>
#include "cell.h"
#include "point.h"
#include "defbuild.h"
#include <map> 
#include <vector>
using std::string;
using std::map;
using std::vector;

namespace Prog4
{
	class board;

    class charact
	{
	private:
		string name;
		int maxhealth;
		int health;
	    int gold;
	public:
		charact() : name(""), maxhealth(0), health(0), gold(0) {}
		charact(string, int, int, int);
		string getname() { return name; }
		int getmaxhealth() { return maxhealth; }
		int gethealth() { return health; }
		int getgold() { return gold; }
		friend class enemy;
		friend class castle;
		void reducehealth(int a) { health -= a; }
		void setname(string a) { name = a; }
		void sethealth(int a) { maxhealth = a; health = a; }
		void addgold(int a) { gold += a; }
	};

	class enemy
	{
	private:
		point coord;
		point prev;
		charact tab;
		magic eff;
		int speed;
		int time;
		static charact sten;
	public:
		enemy() : coord(), prev(), tab(), eff(), speed(0), time(0) {}
		enemy(point a, int b) : coord(a), prev(a), tab(), eff(), speed(b), time(b) {}
		~enemy() {};
		void setcoord(point a) { coord = a; }
		void setprev(point a) { prev = a; }
		void zeromag() { eff.poison = 0; eff.slowdown = 0; eff.weaking = 0; }
		void setspeed(int t) { speed = t; }
		void settime(int t) { time-=t; }
		void settab() { tab = sten; }
		point getcoord() { return coord; }
		int gettime() { return time; }
		friend class castle;
		friend class board;
		int go(board &, vector <defbuilding <magictrap> > &b);
	};

	class castle
	{
	private:
		point coord;
		charact tab;
		static charact stcast;
	public:
		castle() : coord(0, 0), tab() {};
		castle(point a, charact b) : coord(a), tab(b) {};
		~castle() {};
		friend class defbuilding <tower>;
		int gethealth() { return tab.health; }
		int getmaxhealth() { return tab.maxhealth; }
		string getname() { return tab.getname(); }
		int getx() { return coord.getx(); }
		int gety() { return coord.gety(); }
		int getgold() { return tab.getgold(); }
		charact getstcast() { return stcast; }
	    void buy(defbuilding <tower>);
		void buy(defbuilding <magictower>);
		void buy(defbuilding <magictrap>);
		int takedamage(enemy);
	};

	struct pair
	{
		enemy enen;
		int t;
	};

	class dungeon
	{
	private:
		point coord;
		map <int, pair> time;
	public:
		dungeon(point a): coord(a){};
		~dungeon() {};
		map <int, pair> getmap() { return time; }
		void settime(int i, int k) { time[i].t+=k; }
		void setcoord(point a) { coord = a; }
		void setmap(int i, enemy en, int a) { time[i] = { en, a }; }
		int gettime(int i) { return time[i].t; }
		enemy getenemy(int i) { return time[i].enen; }
		void make(enemy);
		void makebytime();
	};

	class board
	{
	private:
		point size;
		cell **field;
		/*vector <enemy> en;
		vector <defbuilding<magictower>> mt;
		vector <defbuilding<magictrap>> mtr;
		vector <defbuilding<tower>> t;*/
	public:
		board(point a);
		~board() { delete[] field; }
		board &operator =(const board &);
		board &operator =(board &&);
		friend class enemy;
		void rand();
		void manual();
		point getsize() const { return size; }
		int getsizex() const { return size.x; }
		int getsizey() const { return size.y; }
		void changesize(unsigned int x, unsigned int y);
		int gettype(unsigned int x, unsigned int y);
		void addtower(const point);
		bool iscorrect();
		void printsize() const;
		void printfield() const;
		void printall(vector <defbuilding<tower>> &v1, vector <defbuilding<magictower>> &v2, vector <defbuilding<magictrap>> &v3, vector <enemy> &env) const;
		point findcast();
		point finddun(int a);
		template<class T>
		defbuilding<T> findtower(vector <defbuilding<T>> &v1, int x, int y);
	};
}

#endif
