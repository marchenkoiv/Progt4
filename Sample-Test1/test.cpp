#include "pch.h"
#include "../Progt4/Board.cpp"
#include "../Progt4/point.cpp"
#include "../Progt4/cell.cpp"
#include "../Progt4/units.cpp"
#include "../Progt4/defbuild.cpp"



TEST(Point, PointConstructor)
{
	Prog4::point a;
	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	Prog4::point a1(1, 2);
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(2, a1.gety());
}

TEST(Point, PointOperations)
{
	Prog4::point a1(3, 4), a2, a3(3, 4);
	ASSERT_EQ(5, a1.dist(a2));
	ASSERT_EQ(true, a1 == a3);
	ASSERT_EQ(false, a2 == (a1));
	ASSERT_EQ(true, a1 != (a2));
	ASSERT_EQ(false, a3 != (a1));
}

TEST(Cell, CellConstructors)
{
	Prog4::cell a, a1(1, 2);
	Prog4::point b, b1(1, 2);
	ASSERT_EQ(0, a.getcoord().getx());
	ASSERT_EQ(0, a.getcoord().gety());
	ASSERT_EQ(1, a1.getcoord().getx());
	ASSERT_EQ(2, a1.getcoord().gety());
	ASSERT_EQ(1, a.gettype());
	ASSERT_EQ(1, a1.gettype());
	Prog4::cell a3(b1), a4(b1, 3);
	ASSERT_EQ(1, a3.getcoord().getx());
	ASSERT_EQ(2, a3.getcoord().gety());
	ASSERT_EQ(1, a4.getcoord().getx());
	ASSERT_EQ(2, a4.getcoord().gety());
	ASSERT_EQ(1, a3.gettype());
	ASSERT_EQ(3, a4.gettype());
	ASSERT_ANY_THROW(Prog4::cell a5(b1, 6));
    ASSERT_ANY_THROW(Prog4::cell a6(1, 2, 6));
}

TEST(Cell, CellOperations)
{
	Prog4::cell a, a1(1, 2);
	a.changetype(2);
	ASSERT_EQ(2, a.gettype());
	a1.changetype(3);
	ASSERT_EQ(3, a1.gettype());
	ASSERT_ANY_THROW(a.changetype(6));
	ASSERT_ANY_THROW(a1.changetype(6));
}

TEST(Board, BoardConstructors)
{
	Prog4::point b, b1(1, 2);
	Prog4::board a1(b1), a(b);
	ASSERT_EQ(0, a.getsizex());
	ASSERT_EQ(0, a.getsizey());
	ASSERT_EQ(1, a1.getsizex());
	ASSERT_EQ(2, a1.getsizey());
}

TEST(Board, BoardOperators)
{
	Prog4::point b, b1(4, 6);
	Prog4::board a1(b1), a(b);
	ASSERT_EQ(0, a.getsizex());
	ASSERT_EQ(0, a.getsizey());
	ASSERT_EQ(4, a1.getsizex());
	ASSERT_EQ(6, a1.getsizey());
	a1.rand();
	ASSERT_EQ(true, a1.iscorrect());
	ASSERT_EQ(0, a1.findcast().gety());
	ASSERT_EQ(5, a1.finddun(0).gety());
}

TEST(Charact, CharactConstructors)
{
	Prog4::charact a;
	std::string s = "qaz";
	Prog4::charact a1(s, 20, 20, 10);
	ASSERT_EQ("", a.getname());
	ASSERT_EQ(0, a.getmaxhealth());
	ASSERT_EQ(0, a.gethealth());
	ASSERT_EQ(0, a.getgold());
	ASSERT_EQ("qaz", a1.getname());
	ASSERT_EQ(20, a1.getmaxhealth());
	ASSERT_EQ(20, a1.gethealth());
	ASSERT_EQ(10, a1.getgold());
}

TEST(Charact, CharactOperations)
{
	Prog4::charact a;
	std::string s = "qaz";
	a.setname(s);
	ASSERT_EQ("qaz", a.getname());
	a.sethealth(20);
	ASSERT_EQ(20, a.getmaxhealth());
	ASSERT_EQ(20, a.gethealth());
	a.addgold(100);
	ASSERT_EQ(100, a.getgold());
	a.reducehealth(10);
	ASSERT_EQ(20, a.getmaxhealth());
	ASSERT_EQ(10, a.gethealth());
}

TEST(Castle, CastleConstructors)
{
	Prog4::castle a;
	Prog4::point p(1, 1);
	Prog4::charact ch("name", 20,20,10);
	Prog4::castle a1(p, ch);
	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(1, a1.gety());
	ASSERT_EQ("", a.getname());
	ASSERT_EQ("name", a1.getname());
	ASSERT_EQ(0, a.getmaxhealth());
	ASSERT_EQ(0, a.gethealth());
	ASSERT_EQ(20, a1.getmaxhealth());
	ASSERT_EQ(20, a1.gethealth());
	ASSERT_EQ(0, a.getgold());
	ASSERT_EQ(10, a1.getgold());

}

TEST(Castle, CastleOperations)
{
	Prog4::castle a;
	Prog4::point p(1, 1);
	Prog4::charact ch("name", 20, 20, 10);
	Prog4::castle a1(p, ch);
	Prog4::enemy en;
	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(1, a1.gety());
	ASSERT_EQ("", a.getname());
	ASSERT_EQ("name", a1.getname());
	ASSERT_EQ(0, a.getmaxhealth());
	ASSERT_EQ(0, a.gethealth());
	ASSERT_EQ(20, a1.getmaxhealth());
	ASSERT_EQ(20, a1.gethealth());
	ASSERT_EQ(0, a.getgold());
	ASSERT_EQ(10, a1.getgold());
	a.addgold(10);
	ASSERT_EQ(10, a.getgold());
	a1.addgold(10);
	ASSERT_EQ(20, a1.getgold());
	en.settab1(ch);
	a1.takedamage(en);
	ASSERT_EQ(0, a1.gethealth());
	a.takedamage(en);
	ASSERT_EQ(-20, a.gethealth());
}

TEST(Enemy, EnemyConstructors)
{
	Prog4::point p(1, 1);
	Prog4::enemy a, a1(p, 10);

	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(1, a1.gety());
	ASSERT_EQ(0, a.gettime());
	ASSERT_EQ(0, a.getspeed());
	ASSERT_EQ(0, a.gethealth());
	ASSERT_EQ(10, a1.gettime());
	ASSERT_EQ(10, a1.getspeed());
	ASSERT_EQ(0, a1.gethealth());
	ASSERT_EQ(0, a.getgold());
	ASSERT_EQ(0, a1.getgold());

}

TEST(Enemy, EnemyOperations)
{
	Prog4::point p(1, 1);
	Prog4::charact ch("name", 20, 20, 10);
	Prog4::enemy a, a1(p, 10);

	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(1, a1.gety());
	ASSERT_EQ(0, a.gettime());
	ASSERT_EQ(0, a.getspeed());
	ASSERT_EQ(0, a.gethealth());
	ASSERT_EQ(0, a.getmaxhealth());
	ASSERT_EQ(10, a1.gettime());
	ASSERT_EQ(10, a1.getspeed());
	ASSERT_EQ(0, a1.gethealth());
	ASSERT_EQ(0, a1.gethealth());
	ASSERT_EQ(0, a.getgold());
	ASSERT_EQ(0, a1.getgold());
	a1.settab1(ch);
	ASSERT_EQ("", a.getname());
	ASSERT_EQ("name", a1.getname());
	ASSERT_EQ(0, a.getmaxhealth());
	ASSERT_EQ(0, a.gethealth());
	ASSERT_EQ(20, a1.getmaxhealth());
	ASSERT_EQ(20, a1.gethealth());
	a.setspeed(12);
	ASSERT_EQ(12, a.getspeed());
	a1.settime(1);
	ASSERT_EQ(9, a1.gettime());
	a1.subhealth(10);
	ASSERT_EQ(20, a1.getmaxhealth());
	ASSERT_EQ(10, a1.gethealth());
}

TEST(Dungeon, DugeonConstructors)
{
	Prog4::point p(1, 1);
	Prog4::enemy a, a1(p, 10);
	Prog4::dungeon d(p);
	ASSERT_EQ(1, d.getx());
	ASSERT_EQ(1, d.gety());

}

TEST(Dungeon, DugeonOperations)
{
	Prog4::point p(1, 1), p1(2, 10);
	Prog4::enemy a, a1(p, 10);
	Prog4::dungeon d(p);
	ASSERT_EQ(1, d.getx());
	ASSERT_EQ(1, d.gety());
	d.setmap(0, a, 10);
	ASSERT_EQ(10, d.gettime(0));
	d.setcoord(p1);
	ASSERT_EQ(2, d.getx());
	ASSERT_EQ(10, d.gety());
	d.settime(0, 2);
	ASSERT_EQ(12, d.gettime(0));
}

TEST(Magic, Magic)
{
	Prog4::magic a, b(10, 20, 30), c;
	ASSERT_EQ(10, b.getsl());
	ASSERT_EQ(20, b.getpo());
	ASSERT_EQ(30, b.getwe());
	ASSERT_EQ(0, a.getsl());
	ASSERT_EQ(0, a.getpo());
	ASSERT_EQ(0, a.getwe());
	a += b;
	ASSERT_EQ(10, a.getsl());
	ASSERT_EQ(20, a.getpo());
	ASSERT_EQ(30, a.getwe());
	c = a + b;
	ASSERT_EQ(20, c.getsl());
	ASSERT_EQ(40, c.getpo());
	ASSERT_EQ(60, c.getwe());
}

TEST(MagicTower, MagicTowerConstructors)
{
	Prog4::magictower a;
	ASSERT_EQ(0, a.getdamage());
	ASSERT_EQ(0, a.getrate());
	ASSERT_EQ(0, a.geteff().getsl());
	ASSERT_EQ(0, a.geteff().getpo());
	ASSERT_EQ(0, a.geteff().getwe());
}

TEST(Tower, TowerConstructors)
{
	Prog4::tower a, b(1,2,3,4);
	ASSERT_EQ(0, a.getdamage());
	ASSERT_EQ(0, a.getrate());
	ASSERT_EQ(0, a.geteff().getsl());
	ASSERT_EQ(0, a.geteff().getpo());
	ASSERT_EQ(0, a.geteff().getwe());
	ASSERT_EQ(1, b.getdamage());
	ASSERT_EQ(2, b.getrate());
	ASSERT_EQ(0, b.geteff().getsl());
	ASSERT_EQ(0, b.geteff().getpo());
	ASSERT_EQ(0, b.geteff().getwe());
}

TEST(MagicTrap, MagicTrapConstructors)
{
	Prog4::magictrap a, b(1,2, 3,4,5);
	ASSERT_EQ(0, a.getdamage());
	ASSERT_EQ(0, a.getrate());
	ASSERT_EQ(0, a.geteff().getsl());
	ASSERT_EQ(0, a.geteff().getpo());
	ASSERT_EQ(0, a.geteff().getwe());
	ASSERT_EQ(0, b.getdamage());
	ASSERT_EQ(0, b.getrate());
	ASSERT_EQ(1, b.geteff().getsl());
	ASSERT_EQ(2, b.geteff().getpo());
	ASSERT_EQ(3, b.geteff().getwe());
}

TEST(DefBuilding, DefBuildingConstructors)
{
	Prog4::defbuilding a, a1(1,2);
	Prog4::point p(1, 1);
	Prog4::defbuilding a2(p);
	ASSERT_EQ(1, a.getlevel());
	ASSERT_EQ(1, a1.getlevel());
	ASSERT_EQ(0, a2.getlevel());
	ASSERT_EQ(1, a.gettime());
	ASSERT_EQ(1, a1.gettime());
	ASSERT_EQ(1, a2.gettime());
	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(2, a1.gety());
	ASSERT_EQ(1, a2.getx());
	ASSERT_EQ(1, a2.gety());
}

TEST(DefBuilding, DefBuildingOperations)
{
	Prog4::defbuilding a, a1(1, 2);
	Prog4::point p(1, 1), p1;
	Prog4::defbuilding a2(p);
	ASSERT_EQ(1, a.getlevel());
	ASSERT_EQ(1, a1.getlevel());
	ASSERT_EQ(0, a2.getlevel());
	ASSERT_EQ(1, a.gettime());
	ASSERT_EQ(1, a1.gettime());
	ASSERT_EQ(1, a2.gettime());
	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
	ASSERT_EQ(1, a1.getx());
	ASSERT_EQ(2, a1.gety());
	ASSERT_EQ(1, a2.getx());
	ASSERT_EQ(1, a2.gety());
	a.lvlup();
	a1.lvlup();
	a2.lvlup();
	ASSERT_EQ(2, a.getlevel());
	ASSERT_EQ(2, a1.getlevel());
	ASSERT_EQ(1, a2.getlevel());
	a.setcoord(p);
	ASSERT_EQ(1, a.getx());
	ASSERT_EQ(1, a.gety());
	a.setcoord(p1);
	ASSERT_EQ(0, a.getx());
	ASSERT_EQ(0, a.gety());
}



int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}