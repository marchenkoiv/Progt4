#ifndef _board_
#define _board_
#include <iostream>
#include <vector>
#include "point.h"
#include "cell.h"
#include "defbuild.h"

using std::vector;

namespace Prog4
{

	/*class enemy;
	
	class board
	{
	private:
		point size;
		cell **field;
		vector <enemy> en;
		vector <defbuilding<magictower>> mt;
		vector <defbuilding<magictrap>> mtr;
		vector <defbuilding<tower>> t;
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
	};*/
}
#endif

