#ifdef UNICODE
#undef UNICODE
#endif // UNICODE
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;


extern vector<map<int, double, greater<>>> poly_house;   //使用vector数组存储多项式


//打印多项式（map）
void print(map<int, double, greater<>>& map) {
	//第一项
	auto it = map.begin();
	if (it->first == 0) {           //幂为0,只写系数
		cout << it->second;
	}
	else {                          //幂不为0
		if (abs(it->second) == 1) {   //系数为正负1
			if (it->second > 0) {       //系数为正1
			}
			else {                      //系数为负1
				cout << "-";
			}
		}
		else {                        //系数不为正负1
			cout << it->second;
		}
		if (it->first == 1) {         //幂为1
			cout << "x";
		}
		else {                        //幂不为1或0
			cout << "x^" << it->first;
		}
	}

	//非第一项
	for (it++; it != map.end(); it++) {
		if (it->first == 0) {           //幂为0,只写系数
			if (it->second > 0) {         //系数为正
				cout << " + " << it->second;
			}
			else if (it->second < 0) {    //系数为负
				cout << " - " << -it->second;
			}
		}
		else {                         //幂不为零
			if (abs(it->second) == 1) {  //系数为正负1
				if (it->second > 0) {      //系数为正1
					cout << " + ";
				}
				else {                     //系数为负1
					cout << " - ";
				}
			}
			else {                      //系数不为正负1
				if (it->second > 0) {     //系数为正
					cout << " + " << it->second;
				}
				else {                    //系数为负
					cout << " - " << -it->second;
				}
			}
			if (it->first == 1) {    //幂为1
				cout << "x";
			}
			else {                  //幂不为1
				cout << "x^" << it->first;
			}
		}
	}
}
/* print的测试样例
 5
 0 0
 0 1
 1 0
 0 -1
 -1 1
 */
//多项式相加
void map_add(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2) {
	for (auto it = map2.begin(); it != map2.end(); it++) {
		map1[it->first] += it->second;
		if (map1[it->first] == 0) map1.erase(it->first);
	}
}
//多项式相减
void map_sub(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2) {
	for (auto it = map2.begin(); it != map2.end(); it++) {
		map1[it->first] -= it->second;
		if (map1[it->first] == 0) map1.erase(it->first);
	}
}
//多项式相乘
void map_mul(map<int, double, greater<>>& target, const map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2) {
	for (auto it = map1.begin(); it != map1.end(); it++) {
		for (auto jt = map2.begin(); jt != map2.end(); jt++) {
			target[it->first + jt->first] += it->second * jt->second;
		}
	}
}


/*主操作函数中使用的4大操作函数定义*/
//打印已创建的多项式
void show() {
	if (poly_house.empty()) {
		cout << "目前还没有多项式被创建噢，快来弄一个吧~" << endl;
		return;
	}
	cout << "已创建的多项式如下： " << endl;
	for (int i = 0; i < poly_house.size(); i++) {
		cout << "   No " << i << ". ";
		print(poly_house[i]);
		cout << endl;
	}
	cout << endl;
}

//创建多项式
bool init() {
	map<int, double, greater<>> poly;
	cout << "请输入想要创建的多项式的项数(按0退出)：" << endl;
	int items;
	cin >> items;
	if (items == 0) return true;

	int exp;
	double cef;
	int cnt = 0;
	while (cnt < items) {   // 用cnt代表项数能输入重复项，而用poly.size()不行
		cout << "请谨慎地依次输入第" << cnt << "项的幂与系数：" << endl;
		cin >> exp >> cef;
		if (cef == 0) continue;//不能输入系数为0的项
		else cnt++;           //输入成功
		poly[exp] += cef;
		if (poly[exp] == 0) poly.erase(exp);//处理掉为0的项
	}
	//添加保存的询问
	cout << "请确认您创建的多项式：" << endl << "    ";
	print(poly);
	cout << endl << "1：保存  0：重输一遍" << endl;
	int command;
	cin >> command;
	if (command == 1) {
		poly_house.emplace_back(poly);
		cout << "已保存为No." << poly_house.size() - 1 << endl;
	}
	else {
		return false;
	}
	return true;
}

//执行运算操作,这是重点
void operate() {
	cout << "本计算器目前支持一次只操作两多项式运算噢" << endl;
	//极端条件处理
	if (poly_house.size() < 2) {
		cout << "现在的多项式数量太少啦，多创建些吧" << endl;
		return;
	}

	cout << endl << "目前有" << poly_house.size() << "个多项式,序号为0~" << poly_house.size() - 1 << endl
	     << "（请一次性输入两个数，有前后次序之分噢，输入-1终止运算,输入-2查看已有多项式）" << endl
	     << "请输入想要用来进行操作的多项式的序号: " << endl;

	//输入序号，序号是重要的循环与功能执行的判断条件
	int operand1 = -3, operand2 = -3;
	while (-2 > operand1 || operand1 >= poly_house.size() || -2 > operand2 || operand2 >= poly_house.size()) {
		cin >> operand1 >> operand2;                //获取多项式的序号
		if (operand1 == -2 || operand2 == -2) {     // 输入存在-2
			show();                                 // 则show()

			if (operand1 != -1 && operand2 != -1) { //若同时不存在-1
				cout << "请再次输入：" << endl;     //则循环回去
			} else return;                            //否则直接结束了

			operand1 = operand2 = -3;               //因为输入了-2，所以设置序号以再次循环
			continue;
		}

		if (operand1 == -1 || operand2 == -1) return;//输入-1终止运算

		//输入序号的有效性判断
		if (-1 > operand1 || operand1 >= poly_house.size() || -1 > operand2 || operand2 >= poly_house.size()) {
			cout << "这是无效输入啦，请重新输入噢" << endl;
		} else {    //有效输入，提供确认
			cout << "您选择的2个操作数分别是：" << endl;
			print(poly_house[operand1]);
			cout << "  和  ";
			print(poly_house[operand2]);
			cout << endl;

			//获取运算指令
			int command;
			cout << "请输入您想进行的操作" << endl
			     << "1.两多项式相加" << endl
			     << "2.左多项式减右多项式" << endl
			     << "3.两多项式相乘" << endl
			     << "其它输入将重新输入多项式序号" << endl;
			cin >> command;     //获取指令

			//执行指令
			map<int, double, greater<>> outcome;     //创建一个用于保存运算结果的多项式
			if (command == 1) {                      //执行加法
				outcome = poly_house[operand1];
				map_add(outcome, poly_house[operand2]);
			} else if (command == 2) {               //执行减法
				outcome = poly_house[operand1];
				map_sub(outcome, poly_house[operand2]);
			} else if (command == 3) {               //执行乘法
				map_mul(outcome, poly_house[operand1], poly_house[operand2]);
			}
			else continue;

			//输出结果
			cout << "结果为: ";
			if (outcome.size() == 0) cout << 0 << " （不予保存）" << endl;    //outcome为0则不保存
			else {
				print(outcome);                                               //否则询问是否保存
				cout << endl << "是否保存这个结果(0_no,1_yes): " << endl;
				int if_store;        //输入指令
				cin >> if_store;
				if (if_store) {      //执行指令
					poly_house.emplace_back(outcome);
					cout << "已保存为No." << poly_house.size() - 1 << endl;
				}
			}
		}
	}
}
//删除已有的多项式
void del() {
	if (poly_house.empty()) {
		cout << "残念~目前还没有已创建的多项式噢,没法删啦" << endl;
		return;
	}
	else if (poly_house.size() == 1) {
		cout << endl << "目前有" << poly_house.size() << "个多项式,序号为0" << endl;
	}
	else {
		cout << endl << "目前有" << poly_house.size() << "个多项式,序号为0~" << poly_house.size() - 1 << endl;
	}
	cout << "请输入要删除的多项式的序号（可输入多个，输入“-1”结束，错误输入将忽略，输入9999全部删除并直接结束:" << endl;

	//使用一个优先队列存储要删的位置，之后再逐一删除
	priority_queue<int> pos2del;
	int command;
	while (!poly_house.empty()) {
		cin >> command;
		if (command == -1) break;
		if (command == 9999) {
			poly_house.clear();
			return;
		}
		else if (command > -1 && command < poly_house.size()) {
			pos2del.push(command);
		}
	}
	while (!pos2del.empty()) {
		if (pos2del.top() == -1) break;
		poly_house.erase(poly_house.begin() + pos2del.top());
		pos2del.pop();
	}

}


/*主操作函数实现*/
void start() {
	cout << endl
	     << "请问您这次想要进行的操作：" << endl
	     << "1.查看已创建的多项式" << endl
	     << "2.创建新的多项式" << endl
	     << "3.取两个多项式进行运算" << endl//要有是否保存结果的选项
	     << "4.删除现有的多项式" << endl;
	int command;
	cin >> command;
	switch (command) {
		case 1:
			show();
			break;
		case 2:
			while (!init());
			break;
		case 3:
			operate();
			break;
		case 4:
			del();//可以设置为一次性多删几个
			break;
		case 5:
			break;
		default:
			cout << "这是无效输入啦，请重试噢" << endl;
	}
}

