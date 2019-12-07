#include <iostream>
#include <map>
#include <vector>
#include "units.h"
#include "defbuild.h"
#include "board.h"
#include <ctime>
#include <stdlib.h>
#include <conio.h>

using namespace std;
using namespace Prog4;

charact castle::stcast("Kemerovo", 500, 500, 200);
charact enemy::sten("dog", 20, 20, 1);

int main()
{

	srand(time(0));
	int bb = 1;
	vector <defbuilding<tower>> v1;
	vector <defbuilding<magictower>> v2;
	vector <defbuilding<magictrap>> v3;
	vector <dungeon> dun;
	vector <enemy> env;
	dungeon dd({0, 0});
	int x, y;
	int e = 20;
	int w = 0;
	int count = 0;
	int m = 0;
	int t = 0;
	point zero = { -1, -1 }, pp;
	point p;
	point p1, p2, p3;
	cout << "Enter size of board (x,y)" << endl;
	cin >> p;
	board br(p);
	br.rand();
	br.printfield();
	castle cast = { br.findcast(), cast.getstcast() };
	defbuilding<tower> a, a1;
	defbuilding<magictower> b, b1;
	defbuilding<magictrap> c, c1;
	do
	{
		switch (bb)
		{
		case 1:
			cout << "Enter numer of tower's levels (<5)" << endl;
			int k;
			cin >> k;
			while (!std::cin.good() || k > 5 || k < 1)
			{
				if (!std::cin.good())
				{
					if (std::cin.eof())
						return 0;
					std::cout << "You are wrong! You probably entered the letters" << std::endl;
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::cin >> k;
				}
				else
				{
					std::cout << "You are wrong! Enter correct number" << std::endl;
					std::cin >> k;
				}
			}
			c.setlevels(k);
			a.setlevels(k);
			b.setlevels(k);
			break;
		case 2:
			cout << "Enter coordinates (size of board is ";
			br.printsize();
			cout<< ")" << endl;
			cin >> x>>y;
			while (!std::cin.good() || x<1 || y<1 || x>=br.getsizex()+1 || y >= br.getsizey() + 1)
			{
				if (!std::cin.good())
				{
					if (std::cin.eof())
						return 0;
					std::cout << "You are wrong! You probably entered the letters" << std::endl;
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::cin >> k;
				}
				else
				{
					std::cout << "You are wrong! Enter correct numbers" << std::endl;
					std::cin >> k;
				}
			}
			x--;
			y--;
			a = { x, y };
			try
			{
				br.addtower({ x, y });
				cast.buy(a);
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
				break;
			}
			v1.push_back(a);
			break;
		case 3:
			cout << "Enter coordinates (size of board is ";
			cout << br.getsize();
			cout << ")" << endl;
			cin >> x >> y;
			while (!std::cin.good() || x < 1 || y < 1 || x >= br.getsizex() + 1 || y >= br.getsizey() + 1)
			{
				if (!std::cin.good())
				{
					if (std::cin.eof())
						return 0;
					std::cout << "You are wrong! You probably entered the letters" << std::endl;
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::cin >> k;
				}
				else
				{
					std::cout << "You are wrong! Enter correct numbers" << std::endl;
					std::cin >> k;
				}
			}
			x--;
			y--;
			b = { x, y };
			try
			{
				br.addtower({ x, y });
				cast.buy(b);
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
				break;
			}
			v2.push_back(b);
			break;
		case 4:
			cout << "Enter coordinates (size of board is ";
			br.printsize();
			cout << ")" << endl;
			cin >> x >> y;
			while (!std::cin.good() || x < 1 || y < 1 || x >= br.getsizex() + 1 || y >= br.getsizey() + 1)
			{
				if (!std::cin.good())
				{
					if (std::cin.eof())
						return 0;
					std::cout << "You are wrong! You probably entered the letters" << std::endl;
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::cin >> k;
				}
				else
				{
					std::cout << "You are wrong! Enter correct numbers" << std::endl;
					std::cin >> k;
				}
			}
			x--;
			y--;
			c = { x, y };
			try
			{
				br.addtower({ x, y });
				cast.buy(c);
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			v3.push_back(c);
			break;
		case 5:
			br.printall(v1, v2, v3, env);
			break;
		case 6:
			cin >> e;
			while (!std::cin.good() || e<1 )
			{
				if (std::cin.eof())
					return 0;
				if (!std::cin.good())
				{
					std::cout << "You are wrong! You probably entered the letters" << std::endl;
					std::cin.clear();
					std::cin.ignore(32767, '\n');
				}
				else
					std::cout << "You are wrong! Incorrect number" << std::endl;
				std::cin >> e;
			}
			break;
		case 7:
			while (br.finddun(w) != zero)
			{
				count++;
				pp = br.finddun(w);
				w = pp.getx() + 1;
				dd.setcoord(pp);
				for (int i = 0; i < e; i++)
				{
					enemy en(pp, 5);
					en.settab();
					dd.setmap(i, en, i*10+1);
				}
				dun.push_back(dd);
			}
			do
			{
				for (int j = 0; j < count; j++)
				{
					int y = dun[j].getmap().size();
					for (int k = 0; k < y; k++)
					{
						dun[j].settime(k, -1);
						int m = dun[j].gettime(k);
						if (m == 0)
						{
							env.push_back(dun[j].getenemy(0));
							//dun[j].getmap().erase(dun[j].getmap().begin());
							//y--;
						}
					}
				}
				for (int i = 0; i < env.size(); i++)
				{
					env[i].settime(1);
					if(env[i].gettime()==0)
						env[i].go(br, v3);
					t = cast.getx();
					p1 = {t+1, 0};
					p1 = { t , 1 };
					p1 = { t - 1, 0 };
					if (env[i].getcoord()== p1 || env[i].getcoord() == p2 || env[i].getcoord() == p3)
					{
						cast.takedamage(env[i]);
						env.erase(env.begin()+i);
					}

				}
				system("cls");
				br.printall(v1, v2, v3, env);
				if (_kbhit())
				{
					int c = _getch();
					if (c == 0x1B) break;
				}
			} while (cast.gethealth() > 0 && env.empty() == false);
			if(cast.gethealth() <= 0)
				std::cout << "You lose"<<std::endl;
			else
				std::cout << "You win";
			break;
		case 8:
			cout << "Enter coordinates of tower";
			cin >> x >> y;
			while (!std::cin.good() || x < 1 || y<1)
			{
				if (std::cin.eof())
					return 0;
				if (!std::cin.good())
				{
					std::cout << "You are wrong! You probably entered the letters" << std::endl;
					std::cin.clear();
					std::cin.ignore(32767, '\n');
				}
				else
					std::cout << "You are wrong! Incorrect number" << std::endl;
				std::cin >> x >> y;
			}
			//a1 = br.findtower(v1, x, y);
			//b1 = br.findtower(v2, x, y);
			//c1 = br.findtower(v3, x, y);
			p = { -1, -1 };
			if (a1.getcoord() != p)
			{
				cast.buy(a1);
			}
			if (b1.getcoord() != p)
			{
				cast.buy(b1);
			}
			if (c1.getcoord() != p)
			{
				cast.buy(c1);
			}
			break;
		default:
			std::cout << "Invalid number";
			break;
		}
		std::cout << "0. Exit \n1. Enter number of tower levels\n2. Add new tower\n3. Add new magic tower\n4. Add new magic trap\n5. Print board\n6. Set number of enemies in a dungeon\n7. Start\n8. Level up" << std::endl;
		std::cout << "Enter the next step:  ";
		std::cin >> bb;
		while (!std::cin.good())
		{
			if (std::cin.eof())
				return 0;
			std::cout << "You are wrong! You probably entered the letters" << std::endl;
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cin >> bb;
		}
	} while (bb != 0);
	
	return 0;
}