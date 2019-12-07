#include "cell.h"

namespace Prog4 
{
	cell::cell(int a, int b, int c)
	{
		coord.x = a;
		coord.y = b;
		if (c >= 0 && c <= 2)
			type = c;
		else
			throw std::exception("invalid type");
	}

	cell:: cell(point a, int c) : coord(a), type(c)
	{
		if (c >= 0 && c <= 5)
			type = c;
		else
			throw std::exception("invalid type");
	}

	void cell:: changetype(int c)
	{
		if (c >= 0 && c <= 5)
			type = c;
		else
			throw std::exception("invalid type");
	}

	point cell::getcoord()
	{
		return coord;
	}

};

