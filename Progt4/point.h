#ifndef _point_
#define _point_
#include <iostream>

namespace Prog4
{
	class point
	{
	private:
		int x;
		int y;
	public:
		friend class cell;
		friend class board;
		friend class enemy;
		friend class magictrap;
		//friend class defbuilding<magictrap>;
		point(): x(0), y(0) {}
		point(int a, int b): x(a), y(b) {}
		unsigned int dist(point);
		int getx() { return x; }
		int gety() { return y; }
		bool operator ==(const point&);
		bool operator !=(const point&);
		friend std::istream & operator >> (std::istream &s, point &st);
		friend std::ostream & operator << (std::ostream &s, const point &st);
	};


}
#endif

