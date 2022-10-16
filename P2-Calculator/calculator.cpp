//
// Created by ling on 2022/10/3.
//

#include "calculator.h"

calculator::calculator() : outcome(0), ifshowModel(false)  {}
/*
 * =((3%2+1)*7)
 * ^2/7-0
 * =99))_1=(5%3)^3
 */
void calculator::welcome() {
	cout << endl << "WELCOME�� " << endl
	<< "This a calculator made by linyn." << endl;
	cout << "Now support: +,-,*,/,%,^,=,()" << endl;
	cout << "have a showModel?(1 for yes, other for cancel) :";
	string a;
	cin >> a;
	if(isdigit(a[0]) && stoi(a) == 1){
		ifshowModel = true;
		cout << "(�����������Զ�������ջ��Ԫ��)" << endl;
	}
}
void calculator::perform() {
	try{
		initInput();    // ���ж�ȡ���룬������ȥ�ո񡢼�����ŵ�Ԥ����
		if(ifshowModel) cout << "������ջ" << "\t\t" << "�����ջ" << "\t\t" << "ʣ�������" << "\t" << "�������е�����" << endl;
        calculate();    // ���м��㣨�Ա��δ����Ķ�ȡ��
	}
	catch (const exception& e) // �����쳣����ʱ�׳�
	{
		clearStack();   // ������ջ�����쳣�����Լ�ʵ��'='���������
//		cerr << e.what() << endl;
		cout << "Syntax error here!" << endl;
	}
}
void calculator::initInput() {
	cout << endl << "------------" <<endl;
	cout << "�����룺 " << outcome ;
	getline(std::cin, input, '\n'); // ��ȡһ������

	//�Ƴ��ո�
	input.erase( remove_if(input.begin(), input.end(), [&](char c){return c == ' ';}), input.end());

	// �ȺŴ���
	int pos = input.rfind('=');
	if(pos != -1){
		input = input.substr(pos);
	}

	checkBracket();   // ���ż��,��ƥ�����׳��쳣
}
void calculator::calculate() {
	// ׼����level����
	function<int(char)> level = [](char c){
		int level = -1;
		switch(c){
			case '(':
				level = 0;
				break;
			case '+':
			case '-':
				level = 3;
				break;
			case '*':
			case '/':
			case '%':
				level = 4;
				break;
			case '^':
				level = 5;
				break;
			default:
				throw std::runtime_error{ string {"Syntax error!"}};
		}
		return level;
	};

	nums.push(outcome); // �Ƚ���һ�εĽ��Ĭ������nums
	i = 0; // ��ʼ���±�
	while(true){
		// �ж��Ƿ�ȫ����ջ������ʼ���㣬����������˳�ѭ��
		if (i == input.length()) {
			while (!ops.empty() && nums.size() >= 2) { // �������Ϊ�գ�˵��û������
				oneCalcu();
			}
			// �������������ջ������Ծ������׳��쳣
			if (nums.size() != 1 || !ops.empty()) throw std::runtime_error{ string {"Syntax error!"}};
			break;
		}

		// ��λ�ж�input�е��ַ�
		if (input[i] == '='){ // ��'='���֮ǰ����Ķ�����������һ�εĴ�
			while(!nums.empty()) nums.pop();
			while(!ops.empty()) ops.pop();
			i++;
		}
		else if (input[i] == '('){ // ����'('ֱ������
			ops.push(input[i++]);
		}
		else if (input[i] == ')'){ // ���������')'����һֱ������ֱ��������һ��'('
			while(ops.top() != '(') { oneCalcu(); }
			ops.pop();
			i++;
		}
		else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '^' ){ // ����
			if(i > 0 && (input[i-1] == '+' || input[i-1] == '-' || input[i-1] == '*' || input[i-1] == '/' || input[i-1] == '%' || input[i-1] == '^' )){ // --��-+�ȴ���
				throw std::runtime_error{ string {"Syntax error!"}};
			}
			if(input[i] == '-' && i > 0 && (input[i-1] == '(' || input[i-1] == '=' )){
				nums.push(0);
			}
			if(!ops.empty() && level(ops.top()) >= level(input[i])){
				do{
					oneCalcu();
				} while(!ops.empty() && level(ops.top()) >= level(input[i]));
			}
			else {
				ops.push(input[i++]);
			}
		}
		else if(input[i] >= '0' && input[i] <= '9'){ // ��������
			size_t j {};
			nums.push(stoi(input.substr(i),&j));
			i += j;
		}
		else  // ������ַ����׳��쳣
		{
			throw std::runtime_error{ string {"Syntax error!"}};
		}
	}
	outcome = nums.top(); // ��ȡ���ս��
	nums.pop();           // �������ջ
}

// ����һ������
void calculator::oneCalcu() {
	showModel();
	int result = 0;
	// ��ȡ������
	int rhs = nums.top(); nums.pop();
	int lhs = nums.top(); nums.pop();
	char op = ops.top(); ops.pop();
	switch (op) {
		case '+':
			result = lhs + rhs;
			break;
		case '-':
			result = lhs - rhs;
			break;
		case '*':
			result = lhs * rhs;
			break;
		case '/':
			if(rhs == 0){
				throw std::runtime_error{ string{"Syntax error!"} };
			}
			result = lhs / rhs;
			break;
		case '%':
			if(rhs == 0){
				throw std::runtime_error{ string{"Syntax error!"} };
			}
			result = lhs % rhs;
			break;
		case '^':
			result = pow(lhs, rhs);
			break;
		default:
			throw std::runtime_error{ string{"Syntax error!"} };
	}
	nums.push(result);
}

// ���ż��
void calculator::checkBracket() {
	string toCheckString = input;
	toCheckString.erase(
			remove_if(
					toCheckString.begin(),
					toCheckString.end(),
					[&](char c){return c != '(' && c != ')';}),
			toCheckString.end());

	size_t len = toCheckString.length();
	if(len%2) throw std::runtime_error{ string {"Syntax error!"}};

	pair<char, char> pair = {')', '('};
	stack<char> stk;
	for (char ch: toCheckString) {
		if (ch == ')') {
			if (stk.empty() || stk.top() != '(') {
				throw std::runtime_error{ string {"Syntax error!"}};
			}
			stk.pop();
		}
		else {
			stk.push(ch);
		}
	}
	if(!stk.empty()) throw std::runtime_error{ string {"Syntax error!"}};
}

void calculator::clearStack() {
	while(!nums.empty()) nums.pop();
	while(!ops.empty()) ops.pop();
}


// ��������ģ��ʹ�ö�stack�Ĵ�ӡ��Ϊ����
template <class Container, class Stream>
Stream& printOneValueContainer (Stream& outputstream, const Container& container)
{
	auto beg = container.begin();
	while(beg != container.end())
	{
		outputstream << " " << *beg++;
	}
	return outputstream;
}
template < class Type, class Container>
const Container& container (const std::stack<Type, Container>& stack)
{
	struct HackedStack : private std::stack<Type, Container>
	{
		static const Container& container
				(const std::stack<Type, Container>& stack)
		{
			return stack.*&HackedStack::c;
		}
	};
	return HackedStack::container(stack);
}
template<class Type, template <class Type1, class Container = std::deque<Type1> > class Adapter , class Stream>
Stream& operator<< (Stream& outputstream, const Adapter<Type>& adapter)
{
	return printOneValueContainer(outputstream, container(adapter));
}
void calculator::showModel() {
	if(!ifshowModel) return;
	cout << nums << "\t\t" <<  ops <<"\t\t\t" << input.substr(i) << "\t\t" << ops.top() << endl;
}


