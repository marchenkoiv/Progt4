#include "units.h"
#include "board.h"
#include "point.h"
#include <vector>
//#include "myvec.h"


using namespace std;

namespace Prog4
{
	charact::charact(std::string a, int b, int c, int d)
	{
		name = a;
		maxhealth = b;
		health = c;
		gold = d;
	}

	
	int enemy::go(board &a, vector <defbuilding> &b, castle cast)
	{
		int x, y;
		x = coord.x;
		y = coord.y;
		if (a.field[x][y - 1].type == 0)
		{
			prev = coord;
			coord.y-=1;
		}
		else
		{
			coord.x += 1;
			if (x+1<a.getsizex() && a.field[x + 1][y].type == 0 && prev != coord)
			{
				prev = coord;
			}
			else 
			{
				coord.x -= 1;
				prev = coord;
				coord.x -= 1;
			}
		}
		tab.health -= eff.poison;
		time = speed+eff.slowdown;
		for (unsigned int i = 0; i < b.size(); i++)
		{
			int g = b[i].level-1;
			magic k = b[i].lev[g]->geteff();
			if (coord.dist(b[i].coord) <= b[i].lev[g]->rad)
				eff += k;
		}
		if (tab.health <= 0)
		{
			return 0;
		}
		return 1;
	}

	void castle:: buy(defbuilding a)
	{
		int l = a.getlevel();
		if (tab.gold >= a.lev[l]->cost)
		{
			tab.gold -= a.lev[l]->cost;
			a.lvlup();
		}
		else
			throw std::exception("You don't have that much gold");
	}

	int castle:: takedamage(enemy en)
	{
		tab.health -= en.tab.health;
		return tab.health;
	}

	defbuilding board::findtower(vector <defbuilding> &v1, int x, int y)
	{
		point c(x, y);
		defbuilding k;
		for (int k = 0; k < v1.size(); k++)
		{
			if (v1[k].getcoord() == c)
			{
				//return v1[k];
			}
		}
		k = v1[0];
		k.setcoord({ -1, -1 });
		return k;
	}
};