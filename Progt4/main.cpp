#include <iostream>
#include <map>
#include <vector>
#include "units.h"
#include "defbuild.h"
#include "board.h"
#include <ctime>
#include <stdlib.h>
#include <conio.h>
//#include "myvec.h"
//#include <SDL2/SDL.h>

using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using namespace Prog4;

charact castle::stcast("TTT", 500, 500, 200);
charact enemy::sten("dog", 20, 20, 5);

int main()
{
	/*if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *min = SDL_CreateWindw(); SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr) 
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}*/


	srand(time(0));
	int bb = 1;
	vector <defbuilding> v1;
	vector <defbuilding> v2;
	vector <defbuilding> v3;
	vector <enemy> env;
	dungeon dd({ 0, 0 });
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
	tower v11;
	magictower v22;
	magictrap v33;
	castle cast = { br.findcast(), cast.getstcast() };
	defbuilding a, a1;
	defbuilding b, b1;
	defbuilding c, c1;
	defbuilding *gr;
	std::vector <dungeon> dun;
	int de = 0;
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
			a.setlevels(k, &v11);
			b.setlevels(k, &v22);
			c.setlevels(k, &v33);
			break;
		case 2:
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
			gr = new defbuilding;
			a.setcoord({ x, y });
			try
			{
				br.addtower({ x, y });
				cast.buy(a);
				*gr = a;
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
				break;
			}
			v1.push_back(*gr);
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
			gr = new defbuilding;
			b.setcoord({ x, y });
			b.setlevels(k, &v22);
			try
			{
				br.addtower({ x, y });
				cast.buy(b);
				*gr = b;
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
				break;
			}
			v2.push_back(*gr);
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
			gr = new defbuilding;
			c.setcoord({ x, y });
			try
			{
				br.addtower({ x, y });
				cast.buy(c);
				*gr = c;
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			v3.push_back(*gr);
			break;
		case 5:
			br.printall(v1, v2, v3, env);
			break;
		case 6:
			cin >> e;
			while (!std::cin.good() || e < 1)
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
					enemy *en=new enemy;
					enemy ene(pp, 5);
					*en = ene;
					en->settab();
					dd.setmap(i, *en, i * 10 + 1);
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
				for (int i = 0; i < v1.size(); i++)
				{

					int q = -1;
					v1[i].settime(-1);
					if (v1[i].gettime() == 0)
					{
						q=v1[i].shot(env, cast);
						v1[i].settime(25 / v1[i].getrate());
						if (q == 2)
						{
							cast.addgold(env[i].getgold());
							env.erase(env.begin()+=i );
							de++;
						}
					}
				}
				for (int i = 0; i < v2.size(); i++)
				{
					int q = -1;
					v2[i].settime(-1);
					if (v2[i].gettime() == 0)
					{
						q=v2[i].shot(env, cast);
						v2[i].settime(25 / v2[i].getrate());
					}
					if (q == 2)
					{
						cast.addgold(env[i].getgold());
						env.erase(env.begin()+=i );
						de++;
					}
				}
				for (int i = 0; i < env.size(); i++)
				{
					int q = -1;
					env[i].settime(1);
					if (env[i].gettime() == 0)
						q = env[i].go(br, v3, cast);

					t = cast.getx();
					p1 = { t + 1, 0 };
					p1 = { t , 1 };
					p1 = { t - 1, 0 };
					if (env[i].getcoord() == p1 || env[i].getcoord() == p2 || env[i].getcoord() == p3)
					{
						cast.takedamage(env[i]);
						env.erase(env.begin()+=i);
					}
					if (q == 0)
					{
						cast.addgold(env[i].getgold());
						env.erase(env.begin()+=i);
						de++;
					}

				}
				system("cls");
				br.printall(v1, v2, v3, env);
				cout << "Your gold: " << cast.getgold() << endl;
				cout << "Number of enemies: " << env.size() << endl;
				cout << "Dead enemies: " << de << endl;
				if (_kbhit())
				{
					int c = _getch();
					if (c == 0x1B) break;
				}
			} while (cast.gethealth() > 0 && env.empty() == false);
			if (cast.gethealth() <= 0)
				std::cout << "You lose" << std::endl;
			else
				std::cout << "You win"<< std::endl;
			break;
		case 8:
			cout << "Enter coordinates of tower";
			cin >> x >> y;
			while (!std::cin.good() || x < 1 || y < 1)
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