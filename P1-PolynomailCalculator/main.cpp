/*
 * version2.0
 * 1.0版本是自己造轮子，用链表实现，写了400行由于太复杂不好调试遂放弃
 * 2.0版本使用的是stl自带的map来表示多项式，用vector存储已创建的多项式
 * 3.0版本学了UI,但半途而废了，以后直接学MFC
 *
 */

//#include <graphics.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

/*设置计算器窗口样式*/
void setwindow();

/*主操作函数声明*/
void start();

/*主操作函数中使用的4大操作函数声明*/
//打印已创建的多项式
void show();
//创建多项式
bool init();
//执行运算操作,这是重点
void operate();
//删除已有的多项式
void del();

/*在下面的4个操作函数中使用的小函数声明，实现在另一个cpp文件*/
//打印多项式（map）
void print(map<int, double, greater<>>& map);
//多项式相加
void map_add(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2);
//多项式相减
void map_sub(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2);
//多项式相乘
void map_mul(map<int, double, greater<>>& target, const map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2);

//使用map<int,double,greater<>>表示多项式
vector<map<int, double, greater<>>> poly_house;   //使用vector数组存储多项式

/*程序入口*/
int main() {

	cout << " ________________________________________ " << endl
	     << "|*                                        *|" << endl
	     << "|*       欢迎使用Linyn的多项式计算器      *|" << endl
	     << "|*                                        *|" << endl
	     << "|* 本计算器支持多项式加减乘法与多项式存储 *|" << endl
	     << "|*                                        *|" << endl
	     << "|*                        a work by Linyn *|" << endl
	     << "|*________________________________________*|" << endl;
	while (true) {
		cout << endl << "请输入您想要进行的操作（0.关闭计算器 1.选择需要的操作）" << endl;
		int command;
		cin >> command;
		switch (command) {
			case 0:         //程序退出位置
				cout << "拜拜~" << endl;
				return 0;
			case 1:
				start();    //进入主功能程序
				break;
			default:
				cout << "这是无效输入啦，请重试噢" << endl;
		}
	}
}



