#include <iostream>
#include <string>
#include <cstdio>
#include <time.h>
using namespace std;
/*
����4������������������ȷ�𰸣������Ƿ��ܵõ�24�㣬
����n��4��int�ռ䣬������4���������
str����һ����ȷ�����
����bool��
�����24���򷵻��棬
���򷵻ؼ٣�
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
����n������������24�����4�����֣�
str����ҵ����룬
b����4�����ܷ����24�㣬
���ش��Ƿ���ȷ��
*/
bool calc(const int *n,const string &str,bool b)
{
	return true;
}

int main()
{
	int n[4];//��4��1-10���������
	string answer;//����ȷ�𰸣�
	string player;//����ҵĴ𰸣�
	bool can;//���Ƿ��ܵõ�24�㣬
	bool right;//����Ҵ��Ƿ���ȷ��
	int tstart,tend;//��ʱ��
	int total;//ʤ��������
	bool win;//�Ƿ�һֱʤ����
	
	win=true;
	while(win)
	{
		total=0;//��ʼ����
		can=calc24(n,answer);//����4������������������ȷ�𰸣������Ƿ��ܵõ�24�㣬
		cout<<n[0];//
		for(int i=1;i<4;++i)
		{
			cout<<";"<<n[i];
		}
		cout<<endl;//���4���������
		cout<<"����24��"<<endl;//
		cout<<"���뺬����4 �����ֵ�һ����������ʽ�ӣ�"<<endl;
		cout<<"����ֻ��ʹ�üӡ������ˡ��������ţ�"<<endl;
		cout<<"���ĸ����޷���������õ�24��������0��"<<endl;//�����ʾ��Ϣ��
		tstart=time(0);//��ʼ��ʱ��
		cin>>player;//�������𰸣�
		tend=time(0);//��ʱ������
		right=calc(n,player,can);//���㲢������Ҵ��Ƿ���ȷ��
		
		cout<<"�������� "<<tend-tstart<<" �룬"<<endl;
		if(right)
		{
			++total;
			cout<<"��ϲ�㣬����ȷ��"<<endl;
			cout<<player<<" == 24 "<<endl;
			cout<<"Ŀǰ���ƴ�� "<<total<<" ����"<<endl;
		}
		else
		{
			cout<<"���ź����𰸴���"<<endl;
			win=false;
			if(can)
			{
				cout<<"�õ�24�����ȷ����Ϊ��"<<endl;
				cout<<answer<<endl;
			}
			else
			{
				cout<<"��ʵ��4�������ǵò���24��ģ�"<<endl;
			}
		}
	}
	return 0;
}
