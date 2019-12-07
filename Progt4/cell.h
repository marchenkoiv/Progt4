#ifndef _cell_
#define _cell_
#include <iostream>
#include "point.h"

namespace Prog4
{

	class cell
	{
	private:
		point coord;
		int type;
	public:
		friend class board;
		friend class enemy;
		cell() : coord(), type(1) {}
		cell(point a, int c=1);
		cell(int a, int b, int c=1);
		point getcoord();
		int gettype() { return type; }
		void changetype(int k);
	};

}
#endif

