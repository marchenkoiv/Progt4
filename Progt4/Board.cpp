//0-дорога
//1-поле
//2-лес
//3-замок
//4-логово
//5-башня

//#include "myvec.h"
#include "units.h"
#include <windows.h> 

namespace Prog4
{

	board::board(point a) : size(a)
	{
		int m = a.x, n = a.y;
		field = new cell*[m];
		for (int i = 0; i < a.x; i++)
		{
			field[i] = new cell[n];
		}
	}

	board & board::operator =(const board &st)
	{
		if (this != &st)
		{
			size = st.size;
			delete[] field;
			field = new cell*[size.x];
			for (int i = 0; i < size.x; i++)
			{
				field[i] = new cell[size.y];
			}
			for (int i = 0; i < size.x; ++i)
				for (int j = 0; j < size.y; j++)
				{
					field[i][j] = st.field[i][j];
				}
		}
		return *this;
	}

	board & board::operator =(board &&st)
	{
		point tmp = size;
		size = st.size;
		st.size = tmp;
		cell **ptr = field;
		field = st.field;
		st.field = ptr;
		return *this;
	}

	int board::gettype(unsigned int x, unsigned int y)
	{
		return field[x][y].type;
	}

	void board::addtower(point b)
	{
		if (field[b.x][b.y].type == 1)
		{
			field[b.x][b.y].type = 5;
		}
		else
			throw std::exception("incorrect coordinate");
	}

	bool board::iscorrect()
	{
		int a = 0, b = 0;
		for (int i = 0; i < size.x; i++)
			for (int j = 0; j < size.y; j++)
			{
				if (field[i][j].type == 3)
					a++;
				if (field[i][j].type == 4)
					b++;
			}
		if (a == 1 && b > 0)
			return true;
		else
			return false;
	}


	void board::changesize(unsigned int x, unsigned int y)
	{
		size.x = x;
		size.y = y;
	}

	void board::manual()
	{
		int t;
		for (int i = 0; i < size.x; i++)
			for (int j = 0; j < size.y; j++)
			{
				std::cin >> t;
				field[i][j].type = t;
			}
	}

	void board::rand()
	{
		int t = 0, k = 0, m = 0, c = 0, cast = 0, h = 0;
		for (int i = 0; i < size.x; i++)
			for (int j = 0; j < size.y; j++)
			{
				t = 1 + std::rand() % 2;
				field[i][j].type = t;
			}
		cast = std::rand() % (size.x);
		field[cast][0].type = 3;
		k = 1 + std::rand() % (size.x) / 2;
		m = size.y - 3 - std::rand() % (size.y) / 4;
		for (int i = 0; i < k; i++)
		{
			t = std::rand() % (size.x-1);
			if (field[t][size.y - 1].type != 4)
				c++;
			field[t][size.y - 1].type = 4;
			for (int j = m; j < size.y - 1; j++)
				field[t][j].type = 0;
		}
		int a = -1, b = -1;
		for (int i = 0; i < size.x; i++)
		{
			if (field[i][m].type == 0)
			{
				b = i;
				if (a == -1)
					a = i;
			}
		}
		for (int i = a; i < b + 1; i++)
		{
			field[i][m].type = 0;
		}
		k = 1 + std::rand() % (size.y / 2);
		if (c > 0 && a != b)
			h = a + std::rand() % (b - a);
		else
			h = a;
		for (int i = 0; i < k; i++)
		{
			int h1;
			t = std::rand() % (m - 1);
			while (t == 1)
				t = std::rand() % (m - 1);
			h1 = std::rand() % size.x;
			if (i == k - 1)
				h1 = cast;
			if (t == 0)
			{
				for (int j = t; j < m + 1; j++)
				{
					field[h][j].type = 0;
				}
				if (h > cast)
				{
					for (int j = cast; j < h; j++)
					{
						field[j][t].type = 0;
					}
				}
				if (h < cast)
				{
					for (int j = h; j < cast; j++)
					{
						field[j][t].type = 0;
					}
				}
				break;
			}
			if (i == k - 1)
				t = 0;
			for (int j = t; j < m + 1; j++)
			{
				field[h][j].type = 0;
			}
			if (h1 > h)
			{
				for (int j = h; j < h1; j++)
				{
					field[j][t].type = 0;
				}
			}
			if (h1 < h)
			{
				for (int j = h1; j < h; j++)
				{
					field[j][t].type = 0;
				}
			}
			h = h1;
			m = t;

		}
		field[cast][0].type = 3;
	}

	void board::printfield() const
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < size.x; i++)
		{
			for (int j = 0; j < size.y; j++)
			{
				switch (field[i][j].type)
				{
				case 0:
					SetConsoleTextAttribute(hConsole, 3);
					std::cout << "=";
					break;
				case 1:
					SetConsoleTextAttribute(hConsole, WHITEONBLACK);
					std::cout << ".";
					break;
				case 2:
					SetConsoleTextAttribute(hConsole, WHITEONBLACK);
					std::cout << "^";
					break;
				case 3:
					SetConsoleTextAttribute(hConsole, 7);
					std::cout << "#";
					break;
				case 4:
					SetConsoleTextAttribute(hConsole, 5);
					std::cout << "*";
					break;
				case 5:
					SetConsoleTextAttribute(hConsole, 2);
					std::cout << "+";
					break;
				default:
					break;
				}
			}
			std::cout << std::endl;
		}
	}

	void board::printsize() const
	{
		std::cout << size;
	}

	point board::findcast()
	{
		int i = 0;
		while (field[i][0].type != 3)
		{
			i++;
		}
		return { i, 0 };
	}

	point board::finddun(int i)
	{
		while (i < size.x - 1 && field[i][size.y - 1].type != 4)
		{
			i++;
		}
		if (i == size.x - 1)
			return { -1, -1 };
		return { i, size.y - 1 };
	}

	void board::printall(vector <defbuilding> &v1, vector <defbuilding> &v2, vector <defbuilding> &v3, vector <enemy> &env) const
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int t = 0;
		char p;
		for (int i = 0; i < size.x; i++)
		{
			for (int j = 0; j < size.y; j++)
			{
				point c(i, j);
				switch (field[i][j].type)
				{
				case 0:
					t = 0;
					for (int k = 0; k < env.size(); k++)
					{
						if (env[k].getcoord() == c)
						{
							SetConsoleTextAttribute(hConsole, 4);
							std::cout << "@";
							t++;
							break;
						}
					}
					if (t == 0)
					{
						SetConsoleTextAttribute(hConsole, 3);
						std::cout << "=";
					}
					break;
				case 1:
					SetConsoleTextAttribute(hConsole, WHITEONBLACK);
					std::cout << ".";
					break;
				case 2:
					SetConsoleTextAttribute(hConsole, WHITEONBLACK);
					std::cout << "^";
					break;
				case 3:
					SetConsoleTextAttribute(hConsole, 7);
					std::cout << "#";
					break;
				case 4:
					SetConsoleTextAttribute(hConsole, 5);
					std::cout << "*";
					break;
				case 5:
					SetConsoleTextAttribute(hConsole, 8);
					for (int k = 0; k < v1.size(); k++)
					{
						if (v1[k].getcoord() == c)
						{
							p = ('a' + v1[k].getlevel()-1);
							std::cout << p;
							break;
						}
					}
					for (int k = 0; k < v2.size(); k++)
					{
						if (v2[k].getcoord() == c)
						{
							p = ('A' + v2[k].getlevel()-1);
							std::cout << p;
							break;
						}
					}
					for (int k = 0; k < v3.size(); k++)
					{
						if (v3[k].getcoord() == c)
						{
							p = '+';
							std::cout << p;
							break;
						}
					}
					break;
				default:
					break;
				}
			}
			std::cout << std::endl;
		}
	}

};