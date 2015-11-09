#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <time.h>
#define DATA "calc24.dat"
#define TEMP "calc24.dat~"
using namespace std;
enum
{ MENU = 1, GAME = 2, OVER = 3, TOP = 4, SETTING = 5, EXIT = 9 };
int timelimit=30;//超时，单位秒，

/*
 * 产生4个随机数，并计算出正确答案，返回是否能得到24点，
 * 数组n有4个int空间，保存这4个随机数，
 * str保存一种正确情况， 返回bool， 能算出24点则返回真，
 * 否则返回假， 
 */
bool calc24(int *n, string & str)
{
	n[0] = 1;
	n[1] = 3;
	n[2] = 5;
	n[3] = 7;
	str = "correct answer...";
	return true;
}

/*
 * 数组n存着用来计算24点的那4个数字， str存玩家的输入，
 * b存那4个数能否算出24点， 返回答案是否正确， 
 */
bool calc(const int *n, const string & str, bool b)
{
	return true;
}

/*
 * 清屏函数， 
 */
void cls()
{
#ifdef WIN32
	system("cls");
#else
	cout << "\033[2J\033[0;0H";
#endif
}

/*
 * 暂停函数， 
 */
void stop()
{
	cout << "输入回车继续，" << endl;
	cin.ignore(100, '\n');
	cin.get();
}

int menu()
{
	cout << "****************************" << endl;
	cout << "*\t1,开始游戏，" << endl;
	cout << "*\t2,设置游戏次数，" << endl;
	cout << "*\t3,排行榜，" << endl;
	cout << "*\t4,离开游戏，" << endl;
	cout << "****************************" << endl;
	bool flag = true;
	while (flag)
	{
		int choise = 0;
		cin >> choise;
		switch (choise)
		{
		case 1:
			return GAME;
			break;
		case 2:
			return SETTING;
			break;
		case 3:
			return TOP;
			break;
		case 4:
			return EXIT;
			break;
		default:
			cout << "输入错误，重新输入，" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
	}
	return EXIT;
}

/*
 * 游戏本体， 参数times表示游戏的次数，
 * 返回胜利的次数， 
 */
int game(int times)
{
	int n[4];					// 存4个1-10的随机数，
	string answer;				// 存正确答案，
	string player;				// 存玩家的答案，
	bool can;					// 存是否能得到24点，
	bool right;					// 存玩家答案是否正确，
	int tstart, tend;			// 计时，
	int score;					// 胜利次数，

	score = 0;					// 初始化，
	while (times-- > 0)
	{
		cls();
		can = calc24(n, answer);	// 产生4个随机数，并计算出正确答案，返回是否能得到24点，
		cout << n[0];			// 
		for (int i = 1; i < 4; ++i)
		{
			cout << ";" << n[i];
		}
		cout << endl;			// 输出4个随机数，
		cout << "计算24点，" << endl;	// 
		cout << "输入含有这4 个数字的一个完整计算式子，" << endl;
		cout << "并且只能使用加、减、乘、除和括号，" << endl;
		cout << "这四个数无法经过计算得到24，则输入0，" << endl;
		cout << "认输则输入=，" << endl;
		cout<<"超过 "<<timelimit<<" 秒就算失败，"<<endl;	// 输出提示信息，
		tstart = time(0);		// 开始计时，
		cin >> player;			// 玩家输入答案，
		tend = time(0);			// 计时结束，
		if (player == "=")
		{
			right = false;
		}
		else
		{
			right = calc(n, player, can);	// 计算并返回玩家答案是否正确，
		}
		
		cout<<"---------------"<<endl;//分割线，
		cout << "这题做了 " << tend - tstart << " 秒，" << endl;
		if(tend-tstart>timelimit)//超时提醒，
		{
			cout<<"可惜，超时了，"<<endl;
		}
		if (right)				// 如果正确，继续，
		{
			if(tend-tstart<=timelimit)//没超时则加一分，
			{
				++score;
			}
			cout << "答案正确，" << endl;
			cout << player << " == 24 " << endl;
		}
		else					// 如果错误，游戏结束，
		{
			cout << "很遗憾，答案错误，" << endl;
			if (can)			// 如果有答案，输出正确答案，
			{
				cout << "得到24点的正确姿势为，" << endl;
				cout << answer << endl;
			}
			else				// 如果没答案，
			{
				cout << "其实这4个数字是得不到24点的，" << endl;
			}
		}
		cout << "目前共计答对 " << score << " 道题，" << endl;
		stop();
	}
	return score;
}

/*
 * 游戏结束时，记录排名， 
 */
void over(int score)
{
	ifstream in;//
	ofstream out;//文件输入输出流，
	string name;				// 当前玩家的名字，上排行榜的话要输入名字，
	string tname;				// 
	int tscore;					// 临时的名字和分数，存排行榜里的名字和分数，
	bool win = false;			// 是否入榜，
	in.open(DATA);				// 读打开数据文件，
	out.open(TEMP);				// 写打开临时文件，
	for (int i = 1; i <= 5; ++i)//循环5次，只记录5人，
	{
		in >> tname >> tscore;
		if (!win && (in.eof() || score > tscore))	// 没入榜的前提下，文件结束(榜上的玩家不够5人)，或分数足够大，则入榜，
		{
			cout << "恭喜你，以 "<<score<<" 分的成绩，夺得了第 " << i << " 名" << endl;
			cout << "请输入你的名字，" << endl;
			cin >> name;
			out << name << " " << score << endl;
			cout<<"记录完成，"<<endl;
			win = true;//标记已入榜，下次循环不进这里，
			stop();
		}
		if (in.eof())			// 文件结束则跳出循环，此次读取失败所以不写入临时文件，
		{
			break;
		}
		out << tname << " " << tscore << endl;//原排行榜的人仍然写入新排行榜，
	}
	in.close();					// 
	out.close();				// 关闭两个文件，
	in.open(TEMP);				// 
	out.open(DATA);
	out << in.rdbuf();
	in.close();
	out.close();				// 把临时文件复制到数据文件，
}

void setting(int &times)
{
	cout << "输入游戏次数，" << endl;
	bool flag = true;
	while (flag)
	{
		cin >> times;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "输入错误，重新输入，" << endl;
		}
		else
		{
			flag = false;
		}
	}
	cout << "游戏次数设置为 " << times << " 次，" << endl;
	stop();
}

void top()
{
	ifstream in;
	in.open(DATA);
	string name;
	int score;
	in >> name >> score;
	for (int i = 1; !in.eof() && i <= 5; ++i)
	{
		cout << "第 " << i << " 名为 " << name << " ，分数为 " << score << " ，" << endl;
		in >> name >> score;
	}
	in.close();
	stop();
}

int main()
{
	int score;
	int flag;
	int times = 10;
	flag = MENU;
	srand(time(0));
	cls();
	while (flag)
	{
		switch (flag)
		{
		case MENU:
			flag = menu();
			break;
		case GAME:
			score = game(times);
			flag = OVER;
			break;
		case OVER:
			over(score);
			flag = MENU;
			break;
		case SETTING:
			setting(times);
			flag = MENU;
			break;
		case TOP:
			top();
			flag = MENU;
			break;
		case EXIT:
			flag = 0;
			break;
		}
		cls();
	}
}
