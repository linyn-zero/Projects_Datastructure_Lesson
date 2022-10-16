//
// Created by ling on 2022/10/3.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
/* 总会将上一次的计算结果放在输入的开头，首次计算前是0
 * =的功能是清除等号之前的所有输入
 * 不支持^^
 */
class calculator {
private:
	stack<int> nums;     // 存储数字
	stack<char> ops;     // 存储运算符
	string input;        // 存储输入
	int outcome;         // 记录上一次计算得到的结果，初始化为0
	bool ifshowModel;    // 是否启动展示模式的输入,默认为关
	size_t i ;           // 输入的下标
public:
	calculator() ;
	void welcome();      // 计算器启动时的介绍语
	void perform();      // 启动一次完整的计算操作（读入、计算），是计算器的核心入口
protected:
	void initInput();    // 进行读取输入，并进行去空格、检查括号等预处理
	void checkBracket(); // 括号检查
	void calculate();    // 进行计算（对本次处理后的读取）
	void oneCalcu();     // 进行单次运算
	void clearStack();   // 清理两栈，是异常处理以及实现'='功能所需的
	void showModel();    // 展示模式
};
#endif //CALCULATOR_CALCULATOR_H
