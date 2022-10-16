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
	cout << endl << "WELCOME！ " << endl
	<< "This a calculator made by linyn." << endl;
	cout << "Now support: +,-,*,/,%,^,=,()" << endl;
	cout << "have a showModel?(1 for yes, other for cancel) :";
	string a;
	cin >> a;
	if(isdigit(a[0]) && stoi(a) == 1){
		ifshowModel = true;
		cout << "(进行运算的永远是运算符栈顶元素)" << endl;
	}
}
void calculator::perform() {
	try{
		initInput();    // 进行读取输入，并进行去空格、检查括号等预处理
		if(ifshowModel) cout << "运算数栈" << "\t\t" << "运算符栈" << "\t\t" << "剩余的输入" << "\t" << "即将进行的运算" << endl;
        calculate();    // 进行计算（对本次处理后的读取）
	}
	catch (const exception& e) // 发现异常，及时抛出
	{
		clearStack();   // 清理两栈，是异常处理以及实现'='功能所需的
//		cerr << e.what() << endl;
		cout << "Syntax error here!" << endl;
	}
}
void calculator::initInput() {
	cout << endl << "------------" <<endl;
	cout << "请输入： " << outcome ;
	getline(std::cin, input, '\n'); // 获取一行输入

	//移除空格
	input.erase( remove_if(input.begin(), input.end(), [&](char c){return c == ' ';}), input.end());

	// 等号处理
	int pos = input.rfind('=');
	if(pos != -1){
		input = input.substr(pos);
	}

	checkBracket();   // 括号检查,不匹配则抛出异常
}
void calculator::calculate() {
	// 准备好level函数
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

	nums.push(outcome); // 先将上一次的结果默认置入nums
	i = 0; // 初始化下标
	while(true){
		// 判断是否全部进栈，是则开始运算，运算结束后退出循环
		if (i == input.length()) {
			while (!ops.empty() && nums.size() >= 2) { // 运算符不为空，说明没计算完
				oneCalcu();
			}
			// 若运算结束后两栈情况不对劲，则抛出异常
			if (nums.size() != 1 || !ops.empty()) throw std::runtime_error{ string {"Syntax error!"}};
			break;
		}

		// 逐位判断input中的字符
		if (input[i] == '='){ // 用'='清除之前输入的东西，包括上一次的答案
			while(!nums.empty()) nums.pop();
			while(!ops.empty()) ops.pop();
			i++;
		}
		else if (input[i] == '('){ // 遇到'('直接填入
			ops.push(input[i++]);
		}
		else if (input[i] == ')'){ // 遇到运算符')'，则一直做运算直到遇见第一个'('
			while(ops.top() != '(') { oneCalcu(); }
			ops.pop();
			i++;
		}
		else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '^' ){ // 符号
			if(i > 0 && (input[i-1] == '+' || input[i-1] == '-' || input[i-1] == '*' || input[i-1] == '/' || input[i-1] == '%' || input[i-1] == '^' )){ // --，-+等错误
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
		else if(input[i] >= '0' && input[i] <= '9'){ // 输入数字
			size_t j {};
			nums.push(stoi(input.substr(i),&j));
			i += j;
		}
		else  // 错误的字符则抛出异常
		{
			throw std::runtime_error{ string {"Syntax error!"}};
		}
	}
	outcome = nums.top(); // 获取最终结果
	nums.pop();           // 清空数字栈
}

// 进行一次运算
void calculator::oneCalcu() {
	showModel();
	int result = 0;
	// 获取操作数
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

// 括号检查
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


// 下面三段模板使得对stack的打印成为可能
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


