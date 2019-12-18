#include "defbuild.h"
//#include "mymap.h"
#include <map>
#include "units.h"


using namespace std;

namespace Prog4
{

	magic magic:: operator += (const magic& a)
	{
		slowdown += a.slowdown;
		poison += a.poison;
		weaking += a.weaking;
		return *this;
	}

	towlevel & towlevel::operator = (const towlevel& ob)
	{
		if (this != &ob)
		{
			cost = ob.cost;
			rad = ob.rad;
		}
		return *this;
	}

	tower & tower::operator = (const tower& ob)
	{

		if (this != &ob)
		{
			cost = ob.cost;
			rad = ob.rad;
			damage = ob.damage;
			rate = ob.rate;
		}
		return *this;
	}

	magictower & magictower::operator = (const magictower& ob)
	{
		if (this != &ob)
		{
			cost = ob.cost;
			rad = ob.rad;
			damage = ob.damage;
			eff = ob.eff;
			rate = ob.rate;
		}
		return *this;
	}

	magictrap & magictrap::operator = (const magictrap& ob)
	{
		
		if (this != &ob)
		{
			cost = ob.cost;
			rad = ob.rad;
		    eff = ob.eff;
		}
		return *this;
	}

	map<int, towlevel*> magictrap::setset( int a)
	{
		map<int, towlevel*> m;
		for (int i = 0; i < a; i++)
		{

			magictrap *b=new magictrap;
			*b = {(i + 1) , (i + 1) , (i + 1) , (i + 1) * 50, (i + 1) * 5 };
			m[i] = b;
		}
		return m;
	}

	map<int, towlevel*> magictower::setset(int a)
	{
		map<int, towlevel*> m;
		magictrap b;
		tower c;
		for (int i = 0; i < a; i++)

		{
			magictower *d = new magictower;
			b = { (i + 1) * 5, (i + 1) * 5, (i + 1) * 5 };
			c = {  (i + 1) * 10, (i + 1) * 10 };
			*d = { b, c , (i + 1) * 50, (i + 1) * 3 };
			m[i] = d;
		}
		return m;
	}

	map<int, towlevel*> tower::setset(int a)
	{
		map<int, towlevel*> m;
		for (int i = 0; i < a; i++)
		{

			tower *b = new tower;
			*b = {(i + 1) * 10, (i + 1) * 10,  (i + 1) * 50, (i + 1) * 3 };
			m[i] = b;
		}
		return m;
	}

	int defbuilding::shot(vector<enemy> env, castle cast)
	{
		int l = this->level;
		for (int k = 0; k < env.size(); k++)
		{
			point c = env[k].getcoord();
			if (coord.dist(c) <= lev[l]->rad)
			{
				env[k].subhealth(lev[l]->getdamage()+env[k].getweaking());
				env[k].seteff(env[k].geteff() + lev[l]->geteff());
				if (env[k].gethealth() <= 0)
				{
					//cast.addgold(env[k].getgold());
					//env.erase(env.begin() + k);
					return 2;
				}
				return 1;
			}
		}
		return 0;
	}

	magic operator +(const magic& p, const magic& k)
	{
		magic a = k, s = p, s1 = k;
		a.poison = s.poison + s1.poison;
		a.slowdown = s.slowdown + s1.slowdown;
		a.weaking = s.weaking + s1.weaking;
		return a;
	}
};