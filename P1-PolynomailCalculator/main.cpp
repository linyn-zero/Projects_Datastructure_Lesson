/*
 * version2.0
 * 1.0�汾���Լ������ӣ�������ʵ�֣�д��400������̫���Ӳ��õ��������
 * 2.0�汾ʹ�õ���stl�Դ���map����ʾ����ʽ����vector�洢�Ѵ����Ķ���ʽ
 * 3.0�汾ѧ��UI,����;�����ˣ��Ժ�ֱ��ѧMFC
 *
 */

//#include <graphics.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

/*���ü�����������ʽ*/
void setwindow();

/*��������������*/
void start();

/*������������ʹ�õ�4�������������*/
//��ӡ�Ѵ����Ķ���ʽ
void show();
//��������ʽ
bool init();
//ִ���������,�����ص�
void operate();
//ɾ�����еĶ���ʽ
void del();

/*�������4������������ʹ�õ�С����������ʵ������һ��cpp�ļ�*/
//��ӡ����ʽ��map��
void print(map<int, double, greater<>>& map);
//����ʽ���
void map_add(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2);
//����ʽ���
void map_sub(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2);
//����ʽ���
void map_mul(map<int, double, greater<>>& target, const map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2);

//ʹ��map<int,double,greater<>>��ʾ����ʽ
vector<map<int, double, greater<>>> poly_house;   //ʹ��vector����洢����ʽ

/*�������*/
int main() {

	cout << " ________________________________________ " << endl
	     << "|*                                        *|" << endl
	     << "|*       ��ӭʹ��Linyn�Ķ���ʽ������      *|" << endl
	     << "|*                                        *|" << endl
	     << "|* ��������֧�ֶ���ʽ�Ӽ��˷������ʽ�洢 *|" << endl
	     << "|*                                        *|" << endl
	     << "|*                        a work by Linyn *|" << endl
	     << "|*________________________________________*|" << endl;
	while (true) {
		cout << endl << "����������Ҫ���еĲ�����0.�رռ����� 1.ѡ����Ҫ�Ĳ�����" << endl;
		int command;
		cin >> command;
		switch (command) {
			case 0:         //�����˳�λ��
				cout << "�ݰ�~" << endl;
				return 0;
			case 1:
				start();    //���������ܳ���
				break;
			default:
				cout << "������Ч����������������" << endl;
		}
	}
}



