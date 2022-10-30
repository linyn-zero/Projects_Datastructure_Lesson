//
// Created by ling on 2022/10/30.
//

#ifndef P4_ARITHMETICEXPRESSIONANDBINARYTREE_EXPRESSIONMANAGER_H
#define P4_ARITHMETICEXPRESSIONANDBINARYTREE_EXPRESSIONMANAGER_H
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <cstring>
//#include "BinaryTree.h"
using std::exception;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::stack;
using std::vector;
using std::queue;
/* ExpressionManager
 * 成员有：
 * 1. 储存表达式的vector（或者使用unordered_map来同时存储string和BinaryTree）
 *    1. 能够重复利用之前出现过的变量的值或表达式
 *    2. 重复出现变量时，能够替代之前的表达式（表达式要有合法检查）
 * 2. build "str" 建立表达式。得存起来：让用户输入name、trees（name可以作为）
 *    1. 检查输入（前缀表达式）的语法正确性
 *    2. 通过前缀表达式建立表达式二叉树
 *    3. 不需要提前算，因为我们需要看见计算的过程
 * 3. print x 以带括号的中缀表示法打印二叉树
 * 4. x = 对变量进行赋值
 * 5. a 变量名
 *   1. 条件不足以求值，以带括号的中缀表示法打印二叉树
 *   2. 条件足以求值，返回值
 * 6. 使用异常处理错误输入
 * 7. check x 检查二叉树
 * 8. marge x,a,y 合并表达式：x、y可以是已有的表达式名，也可以是表达式或单独一个变量。a是运算符
 * 9. calt 返回计算得到的表达式值，条件不足返回异常
 *
 *样例：
 * >>> build
 * name of exp > a
 * trees  > * x x
 * >>> a
 * Error: Wrong input
 * >>> calt a
 * Error: unsufficient conditions.
 * >>> x = 2
 * >>> calt a
 * 4
 * >>> print a
 * x * 2
 */


class ExpressionManager {
private:
	typedef struct BinaryTreeNode{
		char val;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		explicit BinaryTreeNode(char val = 0) : val(val), left(nullptr), right(nullptr) {}
	}*BinaryTree;
	unordered_map<char,int> variable_value;                 // 正在维护的变量值
	unordered_map<string,BinaryTree> trees;                 // 正在维护的二叉树
public:
	~ExpressionManager();                                   // 析构，要拆树
	void setValue(char, int);                         // 设置新的变量值
	void setTree(const string &name, BinaryTree &tree);     // 设置新二叉树
	int getValue(char);                               // 取出变量值,无则返回0作为初值
	BinaryTree getTree(const string &name);                 // 取出树.无则返回nullptr
	BinaryTree getTree(const string &name) const;     // 取出树.无则返回nullptr
	static void welcome();                                         // 欢迎语
	void perform();                                         // 根据用户的输入来确定执行什么操作
	void build(vector<string>& words);                       // 建立前缀表达式二叉树，过程中不求值
	void print(vector<string>& words) const;                   // 打印给定物件，输出中序表达式
	void check(vector<string>& words) const;                // 打印给定物价的二叉树图像
	int calt(vector<string>& words);                               // 检查一个二叉树是否已满足求值条件，满足则求出表达式的值；不存进变量区
	void assign(vector<string>& words);                 // 赋值
	  void printByMidOrder(BinaryTree) const;           // print.以中序输出表达式
	  static int getDepth(BinaryTree) ;                       // check.获取二叉树层数
	  static void printTreelike(BinaryTree, int);             // check.通过深度，图形化打印二叉树
	  int calculate_tree(BinaryTree);                        // calt.计算一棵二叉树的值
	  static int calculate_one(char a, char b, char op);      // 执行单次计算
	  static bool isOps(const char&);                         // 判断是否为支持的运算符类型
	  static void initInput(vector<string>&, string&);        // 把输入拆成vector:words. 以空格,=号作为截断.
	  static string wordsMerge(vector<string>& ,int);         // build.把build的exp整合到一起
	  void buildExceptionDeleting(stack<BinaryTree>&);        // build.在build函数中发生了异常，需要把树拆了，否则内存浪费
	  void treeDeleting(BinaryTree);                          // build&析构.删除一棵二叉树
};


#endif //P4_ARITHMETICEXPRESSIONANDBINARYTREE_EXPRESSIONMANAGER_H

/* Todo:
 * 1. 写头函数
 * 2. 写
 * 3. 检查输入（前缀表达式）的语法正确性,并通过前缀表达式建立表达式二叉树 √
 * 4. 让所有输入以空输入回车结束
 * 5. 检查所有容器，在容器内元素被调用前，检查元素数量是否达到
 * 6. 把输入改成一整行string和vector<string>
 * 7. 单独输入变量名,返回其值
 * 8. 单独输入表达式名,要报错
 * 9. 为变量名赋值,输入常量表达式
 */
