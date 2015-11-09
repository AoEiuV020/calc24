#include <iostream>
#include <string>
#include <cstdio>
#include <time.h>
using namespace std;
/*
产生4个随机数，并计算出正确答案，返回是否能得到24点，
数组n有4个int空间，保存这4个随机数，
str保存一种正确情况，
返回bool，
能算出24点则返回真，
否则返回假，
*/
bool calc24(int *n,string &str)
{
	n[0]=1;
	n[1]=3;
	n[2]=5;
	n[3]=7;
	str="correct answer...";
	return true;
}
/*
数组n存着用来计算24点的那4个数字，
str存玩家的输入，
b存那4个数能否算出24点，
返回答案是否正确，
*/
bool calc(const int *n,const string &str,bool b)
{
	return true;
}

int main()
{
	int n[4];//存4个1-10的随机数，
	string answer;//存正确答案，
	string player;//存玩家的答案，
	bool can;//存是否能得到24点，
	bool right;//存玩家答案是否正确，
	int tstart,tend;//计时，
	int total;//胜利次数，
	bool win;//是否一直胜利，
	
	win=true;
	while(win)
	{
		total=0;//初始化，
		can=calc24(n,answer);//产生4个随机数，并计算出正确答案，返回是否能得到24点，
		cout<<n[0];//
		for(int i=1;i<4;++i)
		{
			cout<<";"<<n[i];
		}
		cout<<endl;//输出4个随机数，
		cout<<"计算24点"<<endl;//
		cout<<"输入含有这4 个数字的一个完整计算式子，"<<endl;
		cout<<"并且只能使用加、减、乘、除和括号，"<<endl;
		cout<<"这四个数无法经过计算得到24，则输入0，"<<endl;//输出提示信息，
		tstart=time(0);//开始计时，
		cin>>player;//玩家输入答案，
		tend=time(0);//计时结束，
		right=calc(n,player,can);//计算并返回玩家答案是否正确，
		
		cout<<"这题做了 "<<tend-tstart<<" 秒，"<<endl;
		if(right)
		{
			++total;
			cout<<"恭喜你，答案正确，"<<endl;
			cout<<player<<" == 24 "<<endl;
			cout<<"目前共计答对 "<<total<<" 道题"<<endl;
		}
		else
		{
			cout<<"很遗憾，答案错误，"<<endl;
			win=false;
			if(can)
			{
				cout<<"得到24点的正确姿势为，"<<endl;
				cout<<answer<<endl;
			}
			else
			{
				cout<<"其实这4个数字是得不到24点的，"<<endl;
			}
		}
	}
	return 0;
}
