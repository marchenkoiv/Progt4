
#include "point.h"

using namespace std;

namespace Prog4
{


	unsigned int point::dist(point a)
	{
		int k;
		k = sqrt((x - a.x)*(x - a.x) + (y - a.y)*(y - a.y));
		return k;
	}

	

	std::istream & operator >> (std::istream &s, point &st)
	{
		int a, b;
		cin >> a >> b;
		if (cin.eof())
			throw std::exception("eof");
		try
		{
			st.x = a;
			st.y = b;
		}
		catch (const std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		return s;
	}

	std::ostream & operator << (std::ostream &s, const point &st)
	{
		s << "(" << st.x << ", " << st.y << ")";
		return s;
	}

	bool point::operator ==(const point& a)
	{
		if (x == a.x && y == a.y)
			return true;
		else
			return false;
	}

	bool point::operator !=(const point& a)
	{
		if (x == a.x && y == a.y)
			return false;
		else
			return true;
	}
	
}