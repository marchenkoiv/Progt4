
#ifndef _units_
#define _units_

#include <iostream>
#include "cell.h"
#include "point.h"
#include "defbuild.h"
//#include "mymap.h"
#include <map>
#include <vector>
//#include "myvec.h"
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
		void settab1(charact a) { tab = a; }
		void seteff(magic a) { eff = a; }
		void subhealth(int a) { tab.health -= a; };
		int getgold() { return tab.getgold(); }
		int gethealth() { return tab.health; };
		int getweaking() { return eff.weaking; }
		magic geteff() { return eff; };
		point getcoord() { return coord; }
		int getx() { return coord.getx(); }
		int gety() { return coord.gety(); }
		int gettime() { return time; }
		int getspeed() { return speed; }
		int getmaxhealth() { return tab.maxhealth; }
		string getname() { return tab.getname(); }
		friend class castle;
		friend class board;
		int go(board &, vector <defbuilding > &b, castle);
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
		friend class defbuilding;
		int gethealth() { return tab.health; }
		int getmaxhealth() { return tab.maxhealth; }
		string getname() { return tab.getname(); }
		int getx() { return coord.getx(); }
		int gety() { return coord.gety(); }
		int getgold() { return tab.getgold(); }
		void addgold(int a) { tab.gold += a; }
		charact getstcast() { return stcast; }
	    void buy(defbuilding);
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
		int getx() { return coord.getx(); }
		int gety() { return coord.gety(); }
		int gettime(int i) { return time[i].t; }
		enemy getenemy(int i) { return time[i].enen; }
		// make(enemy);
		//void makebytime();
	};

	class board
	{
	private:
		point size;
		cell **field;
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
		void printall(vector <defbuilding> &v1, vector <defbuilding> &v2, vector <defbuilding> &v3, vector <enemy> &env) const;
		point findcast();
		point finddun(int a);
		defbuilding findtower(vector <defbuilding> &v1, int x, int y);
	};
}

#endif
