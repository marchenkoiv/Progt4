#include "defbuild.h"
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

	void defbuilding<magictrap>::setlevels( int a)
	{
		towlevel t;
		magictrap b(t);
		for (int i = 0; i < a; i++)
		{
			t = { (i + 1) * 50, (i + 1) * 5 };
			b = { t, (i + 1) * 5, (i + 1) * 5, (i + 1) * 5};
			lev[i] = b;
			//lev.insert(pair<int, magictrap>(i, b));
		}
	}

	void defbuilding<magictower>::setlevels(int a)
	{
		towlevel t;
		magictrap b(t);
		tower c(t);
		magictower d(t, b, c);
		for (int i = 0; i < a; i++)
		{
			t = { (i + 1) * 50, (i + 1) * 5 };
			b = { t, (i + 1) * 5, (i + 1) * 5, (i + 1) * 5 };
			c = { t, (i + 1) * 5, (i + 1) * 5 };
			d = {t,  b, c };
			lev[i] = d;
			//lev.insert(pair<int, magictower>(i, d));
		}
	}

	void defbuilding<tower>::setlevels(int a)
	{
		towlevel t;
		tower b(t);
		for (int i = 0; i < a; i++)
		{
			t = { (i + 1) * 50, (i + 1) * 5 };
			b = {t, (i + 1) * 5, (i + 1) * 5};
			lev[i] = b;
			//lev.insert(pair<int, tower>(i, b));
		}
	}

	/*int defbuilding<tower>::shot(vector<enemy> env)
	{
		int l = this->level;
		for (int k = 0; k < env.size(); k++)
		{
			point c = env[k].getcoord();
			if (coord.dist(c) <= this->lev[l].towlevel.)
			{
				
				break;
			}
		}
	}*/
};