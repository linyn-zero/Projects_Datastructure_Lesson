#ifdef UNICODE
#undef UNICODE
#endif // UNICODE
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;


extern vector<map<int, double, greater<>>> poly_house;   //ʹ��vector����洢����ʽ


//��ӡ����ʽ��map��
void print(map<int, double, greater<>>& map) {
	//��һ��
	auto it = map.begin();
	if (it->first == 0) {           //��Ϊ0,ֻдϵ��
		cout << it->second;
	}
	else {                          //�ݲ�Ϊ0
		if (abs(it->second) == 1) {   //ϵ��Ϊ����1
			if (it->second > 0) {       //ϵ��Ϊ��1
			}
			else {                      //ϵ��Ϊ��1
				cout << "-";
			}
		}
		else {                        //ϵ����Ϊ����1
			cout << it->second;
		}
		if (it->first == 1) {         //��Ϊ1
			cout << "x";
		}
		else {                        //�ݲ�Ϊ1��0
			cout << "x^" << it->first;
		}
	}

	//�ǵ�һ��
	for (it++; it != map.end(); it++) {
		if (it->first == 0) {           //��Ϊ0,ֻдϵ��
			if (it->second > 0) {         //ϵ��Ϊ��
				cout << " + " << it->second;
			}
			else if (it->second < 0) {    //ϵ��Ϊ��
				cout << " - " << -it->second;
			}
		}
		else {                         //�ݲ�Ϊ��
			if (abs(it->second) == 1) {  //ϵ��Ϊ����1
				if (it->second > 0) {      //ϵ��Ϊ��1
					cout << " + ";
				}
				else {                     //ϵ��Ϊ��1
					cout << " - ";
				}
			}
			else {                      //ϵ����Ϊ����1
				if (it->second > 0) {     //ϵ��Ϊ��
					cout << " + " << it->second;
				}
				else {                    //ϵ��Ϊ��
					cout << " - " << -it->second;
				}
			}
			if (it->first == 1) {    //��Ϊ1
				cout << "x";
			}
			else {                  //�ݲ�Ϊ1
				cout << "x^" << it->first;
			}
		}
	}
}
/* print�Ĳ�������
 5
 0 0
 0 1
 1 0
 0 -1
 -1 1
 */
//����ʽ���
void map_add(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2) {
	for (auto it = map2.begin(); it != map2.end(); it++) {
		map1[it->first] += it->second;
		if (map1[it->first] == 0) map1.erase(it->first);
	}
}
//����ʽ���
void map_sub(map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2) {
	for (auto it = map2.begin(); it != map2.end(); it++) {
		map1[it->first] -= it->second;
		if (map1[it->first] == 0) map1.erase(it->first);
	}
}
//����ʽ���
void map_mul(map<int, double, greater<>>& target, const map<int, double, greater<>>& map1, const map<int, double, greater<>>& map2) {
	for (auto it = map1.begin(); it != map1.end(); it++) {
		for (auto jt = map2.begin(); jt != map2.end(); jt++) {
			target[it->first + jt->first] += it->second * jt->second;
		}
	}
}


/*������������ʹ�õ�4�������������*/
//��ӡ�Ѵ����Ķ���ʽ
void show() {
	if (poly_house.empty()) {
		cout << "Ŀǰ��û�ж���ʽ�������ޣ�����Ūһ����~" << endl;
		return;
	}
	cout << "�Ѵ����Ķ���ʽ���£� " << endl;
	for (int i = 0; i < poly_house.size(); i++) {
		cout << "   No " << i << ". ";
		print(poly_house[i]);
		cout << endl;
	}
	cout << endl;
}

//��������ʽ
bool init() {
	map<int, double, greater<>> poly;
	cout << "��������Ҫ�����Ķ���ʽ������(��0�˳�)��" << endl;
	int items;
	cin >> items;
	if (items == 0) return true;

	int exp;
	double cef;
	int cnt = 0;
	while (cnt < items) {   // ��cnt���������������ظ������poly.size()����
		cout << "����������������" << cnt << "�������ϵ����" << endl;
		cin >> exp >> cef;
		if (cef == 0) continue;//��������ϵ��Ϊ0����
		else cnt++;           //����ɹ�
		poly[exp] += cef;
		if (poly[exp] == 0) poly.erase(exp);//�����Ϊ0����
	}
	//��ӱ����ѯ��
	cout << "��ȷ���������Ķ���ʽ��" << endl << "    ";
	print(poly);
	cout << endl << "1������  0������һ��" << endl;
	int command;
	cin >> command;
	if (command == 1) {
		poly_house.emplace_back(poly);
		cout << "�ѱ���ΪNo." << poly_house.size() - 1 << endl;
	}
	else {
		return false;
	}
	return true;
}

//ִ���������,�����ص�
void operate() {
	cout << "��������Ŀǰ֧��һ��ֻ����������ʽ������" << endl;
	//������������
	if (poly_house.size() < 2) {
		cout << "���ڵĶ���ʽ����̫�������ഴ��Щ��" << endl;
		return;
	}

	cout << endl << "Ŀǰ��" << poly_house.size() << "������ʽ,���Ϊ0~" << poly_house.size() - 1 << endl
	     << "����һ������������������ǰ�����֮���ޣ�����-1��ֹ����,����-2�鿴���ж���ʽ��" << endl
	     << "��������Ҫ�������в����Ķ���ʽ�����: " << endl;

	//������ţ��������Ҫ��ѭ���빦��ִ�е��ж�����
	int operand1 = -3, operand2 = -3;
	while (-2 > operand1 || operand1 >= poly_house.size() || -2 > operand2 || operand2 >= poly_house.size()) {
		cin >> operand1 >> operand2;                //��ȡ����ʽ�����
		if (operand1 == -2 || operand2 == -2) {     // �������-2
			show();                                 // ��show()

			if (operand1 != -1 && operand2 != -1) { //��ͬʱ������-1
				cout << "���ٴ����룺" << endl;     //��ѭ����ȥ
			} else return;                            //����ֱ�ӽ�����

			operand1 = operand2 = -3;               //��Ϊ������-2����������������ٴ�ѭ��
			continue;
		}

		if (operand1 == -1 || operand2 == -1) return;//����-1��ֹ����

		//������ŵ���Ч���ж�
		if (-1 > operand1 || operand1 >= poly_house.size() || -1 > operand2 || operand2 >= poly_house.size()) {
			cout << "������Ч��������������������" << endl;
		} else {    //��Ч���룬�ṩȷ��
			cout << "��ѡ���2���������ֱ��ǣ�" << endl;
			print(poly_house[operand1]);
			cout << "  ��  ";
			print(poly_house[operand2]);
			cout << endl;

			//��ȡ����ָ��
			int command;
			cout << "������������еĲ���" << endl
			     << "1.������ʽ���" << endl
			     << "2.�����ʽ���Ҷ���ʽ" << endl
			     << "3.������ʽ���" << endl
			     << "�������뽫�����������ʽ���" << endl;
			cin >> command;     //��ȡָ��

			//ִ��ָ��
			map<int, double, greater<>> outcome;     //����һ�����ڱ����������Ķ���ʽ
			if (command == 1) {                      //ִ�мӷ�
				outcome = poly_house[operand1];
				map_add(outcome, poly_house[operand2]);
			} else if (command == 2) {               //ִ�м���
				outcome = poly_house[operand1];
				map_sub(outcome, poly_house[operand2]);
			} else if (command == 3) {               //ִ�г˷�
				map_mul(outcome, poly_house[operand1], poly_house[operand2]);
			}
			else continue;

			//������
			cout << "���Ϊ: ";
			if (outcome.size() == 0) cout << 0 << " �����豣�棩" << endl;    //outcomeΪ0�򲻱���
			else {
				print(outcome);                                               //����ѯ���Ƿ񱣴�
				cout << endl << "�Ƿ񱣴�������(0_no,1_yes): " << endl;
				int if_store;        //����ָ��
				cin >> if_store;
				if (if_store) {      //ִ��ָ��
					poly_house.emplace_back(outcome);
					cout << "�ѱ���ΪNo." << poly_house.size() - 1 << endl;
				}
			}
		}
	}
}
//ɾ�����еĶ���ʽ
void del() {
	if (poly_house.empty()) {
		cout << "����~Ŀǰ��û���Ѵ����Ķ���ʽ��,û��ɾ��" << endl;
		return;
	}
	else if (poly_house.size() == 1) {
		cout << endl << "Ŀǰ��" << poly_house.size() << "������ʽ,���Ϊ0" << endl;
	}
	else {
		cout << endl << "Ŀǰ��" << poly_house.size() << "������ʽ,���Ϊ0~" << poly_house.size() - 1 << endl;
	}
	cout << "������Ҫɾ���Ķ���ʽ����ţ��������������롰-1���������������뽫���ԣ�����9999ȫ��ɾ����ֱ�ӽ���:" << endl;

	//ʹ��һ�����ȶ��д洢Ҫɾ��λ�ã�֮������һɾ��
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


/*����������ʵ��*/
void start() {
	cout << endl
	     << "�����������Ҫ���еĲ�����" << endl
	     << "1.�鿴�Ѵ����Ķ���ʽ" << endl
	     << "2.�����µĶ���ʽ" << endl
	     << "3.ȡ��������ʽ��������" << endl//Ҫ���Ƿ񱣴�����ѡ��
	     << "4.ɾ�����еĶ���ʽ" << endl;
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
			del();//��������Ϊһ���Զ�ɾ����
			break;
		case 5:
			break;
		default:
			cout << "������Ч����������������" << endl;
	}
}

