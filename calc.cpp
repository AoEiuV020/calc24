#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>
#define DATA "calc24.dat"		// 记录排行榜的文件，
#define TEMP "calc24.dat~"		// 修改排行榜时用到的临时文件，
using namespace std;
stack<char> opr_stk;
stack<double> num_stk;
enum							// 枚举，状态值，
{ MENU = 1, GAME = 2, OVER = 3, TOP = 4, SETTING = 5, EXIT = 9 };
int timelimit = 90;				// 超时，单位秒，

/*
 * 产生4个随机数，并计算出正确答案，返回是否能得到24点，
 * 数组n有4个int空间，保存这4个随机数，
 * str保存一种正确情况， 返回bool， 能算出24点则返回真，
 * 否则返回假，
 */
bool calc24(int *n, string & str);

/*
 * 数组n存着用来计算24点的那4个数字， str存玩家的输入，
 * b存那4个数能否算出24点， 返回答案是否正确，
 */
bool calc(const int *n, const string & str, bool b);

/*
 * 清屏函数，
 */
void cls();

/*
 * 暂停函数，
 */
void stop();
/*
 * 菜单函数，
 */
int menu();

/*
 * 游戏本体， 参数times表示游戏的次数，
 * 返回胜利的次数，
 */
int game(int times);

/*
 * 游戏结束时，记录排名，
 */
void over(int score);

/*
 * 设置游戏次数，
 */
void setting(int &times);

/*
 * 输出排行榜，
 */
void top();

int main()
{
	int score;//记录分数，
	int flag;//记录状态，
	int times = 10;//游戏次数，
	flag = MENU;
	srand(time(0));//设置随机种子，
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

bool calc24(int *n, string & str)	// 生成4个随机数写入n，判断能否得到24，若能将答案写入str
{
	int a, b, c, d;
	n[0] = rand() % 10 + 1;
	n[1] = rand() % 10 + 1;
	n[2] = rand() % 10 + 1;
	n[3] = rand() % 10 + 1;
	a = n[0];
	b = n[1];
	c = n[2];
	d = n[3];
	bool operatorchange(double e, double f, double g, double h, string & str);	// 穷举abcd所有排列
	if (operatorchange(a, b, c, d, str))
		return true;
	if (operatorchange(a, b, d, c, str))
		return true;
	if (operatorchange(a, c, b, d, str))
		return true;
	if (operatorchange(a, c, d, b, str))
		return true;
	if (operatorchange(a, d, b, c, str))
		return true;
	if (operatorchange(a, d, c, b, str))
		return true;
	if (operatorchange(b, a, c, d, str))
		return true;
	if (operatorchange(b, a, d, c, str))
		return true;
	if (operatorchange(b, c, a, d, str))
		return true;
	if (operatorchange(b, c, d, a, str))
		return true;
	if (operatorchange(b, d, a, c, str))
		return true;
	if (operatorchange(b, d, c, a, str))
		return true;
	if (operatorchange(c, a, b, d, str))
		return true;
	if (operatorchange(c, a, d, b, str))
		return true;
	if (operatorchange(c, b, a, d, str))
		return true;
	if (operatorchange(c, b, d, a, str))
		return true;
	if (operatorchange(c, d, a, b, str))
		return true;
	if (operatorchange(c, d, b, a, str))
		return true;
	if (operatorchange(d, a, b, c, str))
		return true;
	if (operatorchange(d, a, c, b, str))
		return true;
	if (operatorchange(d, b, a, c, str))
		return true;
	if (operatorchange(d, b, c, a, str))
		return true;
	if (operatorchange(d, c, a, b, str))
		return true;
	if (operatorchange(d, c, b, a, str))
		return true;
	return false;
}
bool operatorchange(double x, double y, double z, double w, std::string & str)	// 穷举所有可能的运算方式，返回能否算得24，
{
	ostringstream os;
	if ((abs(x + y + z + w - 24)) < 0.0001)
		os << x << "+" << y << "+" << z << "+" << w << "=24" << endl;	// 将计算方式写入os
	else if (abs(x + y + z - w - 24) < 0.0001)
		os << x << "+" << y << "+" << z << "-" << w << "=24" << endl;	// 已去除重复或不能能状况例如x-y-z-w
	else if (abs((x + y) * (z + w) - 24) < 0.0001)
		os << "(" << x << "+" << y << ")*(" << z << "+" << w << ")=24" << endl;
	else if (abs((x - y) * (z + w) - 24) < 0.0001)
		os << "(" << x << "-" << y << ")*(" << z << "+" << w << ")=24" << endl;
	else if (abs((x - y) * (z - w) - 24) < 0.0001)
		os << "(" << x << "-" << y << ")*(" << z << "-" << w << ")=24" << endl;
	else if (abs((x + y + z) * w - 24) < 0.0001)
		os << "(" << x << "+" << y << "+" << z << ")*" << w << "=24" << endl;
	else if (abs((x - y - z) * w - 24) < 0.0001)
		os << "(" << x << "-" << y << "-" << z << ")*" << w << "=24" << endl;
	else if (abs((x + y - z) * w - 24) < 0.0001)
		os << "(" << x << "+" << y << "-" << z << ")*" << w << "=24" << endl;
	else if (abs(x * y * z / w - 24) < 0.0001)
		os << x << "*" << y << "*" << z << "/" << w << "=24" << endl;
	else if (abs(x * y * (z + w) - 24) < 0.0001)
		os << x << "*" << y << "*(" << z << "+" << w << ")=24" << endl;
	else if (abs(x * y * (z - w) - 24) < 0.0001)
		os << x << "*" << y << "*(" << z << "-" << w << ")=24" << endl;
	else if (abs(x * y * z - w - 24) < 0.0001)
		os << x << "*" << y << "*" << z << "-" << w << "=24" << endl;
	else if (abs(x * y * z + w - 24) < 0.0001)
		os << x << "*" << y << "*" << z << "+" << w << "=24" << endl;
	else if (abs(x * y * z * w - 24) < 0.0001)
		os << x << "*" << y << "*" << z << "*" << w << "=24" << endl;
	else if (abs((x + y) + (z / w) - 24) < 0.0001)
		os << "(" << x << "+" << y << ")+(" << z << "/" << w << ")" << "=24" << endl;
	else if (abs((x + y) * (z / w) - 24) < 0.0001)
		os << "(" << x << "+" << y << ")*(" << z << "/" << w << ")" << "=24" << endl;
	else if (abs(x * y + z + w - 24) < 0.0001)
		os << x << "*" << y << "+" << z << "+" << w << "=24" << endl;
	else if (abs(x * y + z - w - 24) < 0.0001)
		os << x << "*" << y << "+" << z << "-" << w << "=24" << endl;
	else if (abs(x * (y + z - w) - 24) < 0.0001)
		os << x << "*(" << y << "+" << z << "-" << w << ")=24" << endl;
	else if (abs(x * (y + z) - w - 24) < 0.0001)
		os << x << "*(" << y << "+" << z << ")-" << w << "=24" << endl;
	else if (abs(x * y - z / w - 24) < 0.0001)
		os << x << "*" << y << "-" << z << "/" << w << "=24" << endl;
	else if (abs((x * y - z )/ w - 24) < 0.0001)
		os << x << "(*" << y << "-" << z << ")/" << w << "=24" << endl;
	else if (abs(x * y + z / w - 24) < 0.0001)
		os << x << "*" << y << "+" << z << "/" << w << "=24" << endl;
	else if (abs(x * y - z - w - 24) < 0.0001)
		os << x << "*" << y << "-" << z << "-" << w << "=24" << endl;
	else if (abs(x * y + z * w - 24) < 0.0001)
		os << x << "*" << y << "+" << z << "*" << w << "" << "=24" << endl;
	else if (abs(x * y - z * w - 24) < 0.0001)
		os << x << "*" << y << "-" << z << "*" << w << "=24" << endl;
	else if (abs(x * y - z / w - 24) < 0.0001)
		os << x << "*" << y << "-" << z << "/" << w << "=24" << endl;
	else if (abs(x * (y - z / w) - 24) < 0.0001)
		os << x << "*(" << y << "-" << z << "/" << w << ")=24" << endl;
	else if (abs(x * y / (z * w) - 24) < 0.0001)
		os << x << "*" << y << "/(" << z << "*" << w << ")" << "=24" << endl;
	else if (abs(x * y / (z - w) - 24) < 0.0001)
		os << x << "*" << y << "/(" << z << "-" << w << ")" << "=24" << endl;
	// x/(y z w) ，则y z
	// w必须为小于w或y/z-w或(y-zy-z/w或y/z-w或(y-z)/w或y/(z+-*/w)
	// else if (x/(y+z+w)-24)<0.0001)
	// cout<<x<<</("<<y<<<<z<<""<<w<<")"<<"=24"<<endl;
	// else if (x/(y+z-w)-24)<0.0001)
	// cout<<x<<</("<<y<<<<z<<""<<w<<")"<<"=24"<<endl;
	// else if (x/(y+z*w)-24)<0.0001)
	// cout<<x<<</("<<y<<<<z<<""<<w<<")"<<"=24"<<endl;
	else if (abs(x / (y - z / w) - 24) < 0.0001)
		os << x << "/(" << y << "-" << z << "/" << w << ")" << "=24" << endl;
	else if (abs(x / (y / z - w) - 24) < 0.0001)
		os << x << "/(" << y << "/" << z << "-" << w << ")" << "=24" << endl;
	else if (abs(x / ((y - z) / w) - 24) < 0.0001)
		os << x << "/((" << y << "-" << z << ")/" << w << ")" << "=24" << endl;
	else if (abs(x / (y / z / w) - 24) < 0.0001)
		os << x << "/(" << y << "/" << z << "/" << w << ")" << "=24" << endl;
	else if (abs(x / (y / (z + w)) - 24) < 0.0001)
		os << x << "/(" << y << "/(" << z << "+" << w << ")" << "=24" << endl;
	else if (abs(x / (y / (z - w)) - 24) < 0.0001)
		os << x << "/(" << y << "/(" << z << "-" << w << ")" << "=24" << endl;
	else if (abs(x / (y / (z * w)) - 24) < 0.0001)
		os << x << "/(" << y << "/(" << z << "*" << w << ")" << "=24" << endl;
	else if (abs(x / (y / (z / w)) - 24) < 0.0001)
		os << x << "/(" << y << "/(" << z << "/" << w << ")" << "=24" << endl;
	else
		return false;
	str = os.str();
	return true;
}

bool calc(int *n,const string &str,bool b)
{

	void pop_cal();
	int p_Rank(char);
	int i=0,j=0; //i,j为循环变量
    bool num_flag=0;
    double x=0; //x为玩家输入的字符串中的数字
	int xi=0;//xi是为了用来判断每个给出的数字是否用且只用了一次
	while(!num_stk.empty())
	{
		num_stk.pop();
	}
	while(!opr_stk.empty())
	{
		opr_stk.pop();
	}
	if(str[0]=='0')
	{
		if(b==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	} //判断玩家输入的是否为0，并和正确答案作比较
	else
	{
		for(i=0;i<str.size();i++)
		{
            if((str[i]>='0')&&(str[i]<='9'))//筛选出字符为数字的元素
			{
                x=x*10+str[i]-'0'; //玩家输入的数字
				xi=xi*10+str[i]-'0'; //再存一次玩家输入的数字，用来判断是否用了给的数字
                num_flag=1;
                if(i==str.size()-1)
				{
                    num_stk.push(x);//将数字推入栈中
					for(j=0;j<4;j++)
					{
						if(xi==n[j])
						{
							n[j]=0;//用了给出的数字，则将其赋值0，表示已经用了给的数字
							break;
						}
					}
					if(j==4)
					{
						return false;//循环走出来了，代表玩家并没有用到给的数字，答案错误
					}
					if(xi==0)
					{
						return false;//不会出现数字0，所以出现判定为用没给的数字，答案错误

					}
				}
			}
			else
			{
				if(x)
				{
					num_stk.push(x);
					for(j=0;j<4;j++)
					{
						if(xi==n[j])
						{
							n[j]=0;//用了给出的数字，则将其赋值0，表示已经用了给的数字
							break;
						}
					}
					if(j==4)
					{
						return false;//循环走出来了，代表玩家并没有用到给的数字，答案错误
					}
					if(xi==0)
					{
						return false;//不会出现数字0，所以出现判定为用没给的数字，答案错误
					}
					x=0;
					xi=0;
					num_flag=0;
				}
				if(opr_stk.empty())
					opr_stk.push(str[i]);//字符串结束，依次出栈
				else if(str[i]=='(')
					opr_stk.push(str[i]);
				else if(str[i]==')')
				{
					while(opr_stk.top()!='(')
						pop_cal();
					opr_stk.pop(); //出现括号的处理
				}
				else if(p_Rank(str[i])<=p_Rank(opr_stk.top()))
				{
					pop_cal();
					opr_stk.push(str[i]);
				}  //加减乘除括号优先级的处理
				else
				{
					opr_stk.push(str[i]);
				}
			}
		}
		while(!opr_stk.empty())
			pop_cal();
		double res=num_stk.top();//表达式的结果

		for(j=0;j<4;j++)
		{
			if(n[j]!=0)//用了给的数字，所有数字都会被赋值为0，所以不为0即答案错误
			{
				return false;
			}
		}
		if(fabs(res)-24<0.00001)//表达式所算出的答案是否为24
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
void pop_cal() //计算表达式的结果
{
	char op=opr_stk.top();
	double a,b,res;
	b=num_stk.top();
	num_stk.pop();
	a=num_stk.top();
	num_stk.pop();//得到的数字依次出栈
	switch(op)
	{
		case '+':
			res=a+b;
			break;
		case '-':
			res=a-b;
			break;
		case '*':
			res=a*b;
			break;
		case '/':
			res=a/b; //加减乘除的加入，得出结果
			break;
		default:
			break;
	}
	num_stk.push(res);//即为答案
	opr_stk.pop(); //答案出栈
}

int p_Rank(char x) //优先级
{
	if(x=='(')
		return 0;
	else if(x=='+')
		return 1;
	else if(x=='-')
		return 2;
	else if(x=='*')
		return 3;
	else if(x=='/')
		return 4;
}

void cls()
{
#if defined(WIN32) || defined(__MINGW32__)
	system("cls");
#else
	// cout << "\033[2J\033[0;0H";
	system("clear");
#endif
}

void stop()
{
	cout << "输入回车继续，" << endl;
	cin.ignore(100, '\n');		// 清空输入缓冲，假设输入缓冲小于100字符，
	cin.get();					// 暂停，
}

int menu()
{
	cout << "****************************" << endl;
	cout << "*\t1,开始游戏，" << endl;
	cout << "*\t2,设置游戏次数，" << endl;
	cout << "*\t3,排行榜，" << endl;
	cout << "*\t4,离开游戏，" << endl;
	cout << "****************************" << endl;
	bool flag = true;			// 循环标志，
	while (flag)				// 输入错误的情况循环，
	{
		int choise = 0;
		cin >> choise;
		switch (choise)			// 处理选择，
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
		cout << "超过 " << timelimit << " 秒就算失败，" << endl;	// 输出提示信息，
		tstart = time(0);		// 开始计时，
		cin >> player;			// 玩家输入答案，
		tend = time(0);			// 计时结束，
		if (player == "+")
		{
			return score;
		}
		else if (player == "=")
		{
			right = false;
		}
		else
		{
			right = calc(n, player, can);	// 计算并返回玩家答案是否正确，
		}

		cout << "---------------" << endl;	// 分割线，
		cout << "这题做了 " << tend - tstart << " 秒，" << endl;
		if (tend - tstart > timelimit)	// 超时提醒，
		{
			cout << "可惜，超时了，" << endl;
		}
		if (right)				// 如果正确，继续，
		{
			if (tend - tstart <= timelimit)	// 没超时则加一分，
			{
				++score;
			}
			cout << "答案正确，" << endl;
			if (can)			// 如果有答案，输出正确答案，
			{
				cout << player << " == 24 " << endl;
			}
			else				// 如果没答案，
			{
				cout << "其实这4个数字是得不到24点的，" << endl;
			}
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

void over(int score)
{
	ifstream in;				//
	ofstream out;				// 文件输入输出流，
	string name;				// 当前玩家的名字，上排行榜的话要输入名字，
	string tname;				//
	int tscore;					// 临时的名字和分数，存排行榜里的名字和分数，
	bool win = false;			// 是否入榜，
	in.open(DATA);				// 读打开数据文件，
	out.open(TEMP);				// 写打开临时文件，
	for (int i = 1; i <= 5; ++i)	// 循环5次，只记录5人，
	{
		in >> tname >> tscore;
		if (!win && (!in.good() || score > tscore))	// 没入榜的前提下，文件结束(榜上的玩家不够5人)，或分数足够大，则入榜，
		{
			cout << "恭喜你，以 " << score << " 分的成绩，夺得了第 " << i << " 名"
				<< endl;
			cout << "请输入你的名字，" << endl;
			cin >> name;
			out << name << " " << score << endl;
			cout << "记录完成，" << endl;
			win = true;			// 标记已入榜，下次循环不进这里，
			stop();
		}
		if (!in.good())			// 文件结束则跳出循环，此次读取失败所以不写入临时文件，
		{
			break;
		}
		out << tname << " " << tscore << endl;	// 原排行榜的人仍然写入新排行榜，
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
	cout << "当前设置为， " << times << " 次，" << endl;
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
	for (int i = 1; in.good() && i <= 5; ++i)
	{
		cout << "第 " << i << " 名为 " << name << " ，分数为 " << score << " ，" << endl;
		in >> name >> score;
	}
	in.close();
	stop();
}
