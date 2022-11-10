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
#include <iomanip>
using std::exception;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::stack;
using std::vector;
using std::queue;
/*
    变量
    unordered_map<char,int> variable_value;                 // 正在维护的变量值
	unordered_map<string,BinaryTree> trees;                 // 正在维护的二叉树

    函数
	~ExpressionManager();                                   // 析构，要拆树
	void setValue(char, int);                               // 设置新的变量值
	void setTree(const string &name, BinaryTree &tree);     // 设置新二叉树
	int getValue(char);                                     // 取出变量值,无则返回0作为初值
	BinaryTree getTree(const string &name);                 // 取出树.无则返回nullptr
	BinaryTree getTree(const string &name) const;           // 取出树.无则返回nullptr

	static void welcome();                                  // 欢迎语
	void perform();                                         // 根据用户的输入来确定执行什么操作
	void build(vector<string>& words);                      // 建立前缀表达式二叉树，过程中不求值
	void print(vector<string>& words) const;                // 打印给定二叉树的中序表达式
	void check(vector<string>& words) const;                // 打印给定二叉树的图像
	int calt(vector<string>& words);                        // 求二叉树表达式的值（未知变量初始为0）。不存进变量区
	void merge(vector<string> words);                       // 给定运算符，合并两表达式，获得新名字，不改变原来的两棵树
	void mergeconst(vector<string> words);                  // 将给定二叉树中的能运算的常数运算完成
	void assign(vector<string>& words);                     // 给变量赋值,例: a=1

	BinaryTree buildTree(const string& );                   // 給定前綴表達式string,建樹,返回樹的頭節點
	void printByMidOrder(BinaryTree) const;                 // print.给定二叉树头结点，以中序输出表达式
	static int getDepth(BinaryTree) ;                       // check.给定二叉树，返回层数。
	static void printTreelike(BinaryTree, int);             // check.给定二叉树与其层数，图形化打印二叉树(使用的是线性表满二叉树，在数据较大时对使用大量内存，更正的话会使用两个子树下标数组代替）
	int calculate_tree(BinaryTree);                         // calt.给定一棵二叉树的头结点，计算一棵二叉树的值
	static int calculate_one(int , int , char op);          // calt.给定两个运算数与一个二元运算符，执行单次计算，返回结果
	static bool isOps(const char&);                         // 判断是否为程序支持的运算符类型
	static vector<string> initInput(const string&);         // perform.给定string，拆成vector<string> 以空格,=号作为截断.
	static string wordsMerge(vector<string>& ,int);         // build.给定vector<string>,把其中需要build的exp部分整合到一起
	static void buildExceptionDeleting(stack<BinaryTree>&); // build.给定一棵二叉树的头结点，把树拆了。用于处理build中的异常。需要把树拆了，否则内存浪费
	static void treeDeleting(BinaryTree);                   // build&析构.给定一棵二叉树的头结点，把树拆了。
	int calculate_consts(BinaryTree);                       // merge_const.给定一棵二叉树的头结点，将一颗树能做的常数运算完成
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

	// 成员变量管理者
	void setValue(char, int);                               // 设置新的变量值
	void setTree(const string &name, BinaryTree &tree);     // 设置新二叉树
	int getValue(char);                                     // 取出变量值,无则返回0作为初值
	BinaryTree getTree(const string &name);                 // 取出树.无则返回nullptr
	BinaryTree getTree(const string &name) const;           // 取出树.无则返回nullptr
	// perform函数的接口
	void build(vector<string>& words);                      // 建立前缀表达式二叉树，过程中不求值

	void print(vector<string>& words) const;                // 打印给定二叉树的中序表达式
	void check(vector<string>& words) const;                // 打印给定二叉树的图像
	void list(vector<string>& words) const;                 // 列表化打印二叉树
	int calt(vector<string>& words);                        // 求二叉树表达式的值（未知变量初始为0）。不存进变量区
	void merge(vector<string> words);                       // 给定运算符，合并两表达式，获得新名字，不改变原来的两棵树
	void mergeconst(vector<string> words);                  // 将给定二叉树中的能运算的常数运算完成
	void assign(vector<string>& words);                     // 给变量赋值,例: a=1
	// perform函数接口的接口
	BinaryTree buildTree(const string& );                   // 給定前綴表達式string,建樹,返回樹的頭節點

	void printByMidOrder(BinaryTree) const;                 // print.给定二叉树头结点，以中序输出表达式
	void printlist(BinaryTree, int) const;                  // list.给定二叉树头结点,列表化打印
	static int getDepth(BinaryTree) ;                       // check.给定二叉树，返回层数。
	static void printTreelike(BinaryTree, int);             // check.给定二叉树与其层数，图形化打印二叉树(使用的是线性表满二叉树，在数据较大时对使用大量内存，更正的话会使用两个子树下标数组代替）
	int calculate_tree(BinaryTree);                         // calt.给定一棵二叉树的头结点，计算一棵二叉树的值
	static int calculate_one(int , int , char op);          // calt.给定两个运算数与一个二元运算符，执行单次计算，返回结果
	static bool isOps(const char&);                         // 判断是否为程序支持的运算符类型
	static vector<string> initInput(const string&);         // perform.给定string，拆成vector<string> 以空格,=号作为截断.
	static string wordsMerge(vector<string>& ,int);         // build.给定vector<string>,把其中需要build的exp部分整合到一起
	static void buildExceptionDeleting(stack<BinaryTree>&); // build.给定一棵二叉树的头结点，把树拆了。用于处理build中的异常。需要把树拆了，否则内存浪费
	static void treeDeleting(BinaryTree);                   // build&析构.给定一棵二叉树的头结点，把树拆了。
	void calculate_consts(BinaryTree);                       // merge_const.给定一棵二叉树的头结点，将一颗树能做的常数运算完成

public:
	~ExpressionManager();                                   // 析构，要拆树
	static void welcome();                                  // 欢迎语
	bool perform();                                         // 根据用户的输入来确定执行什么操作
};


#endif //P4_ARITHMETICEXPRESSIONANDBINARYTREE_EXPRESSIONMANAGER_H

/* Todo:
 * 1. 写头函数 √
 * 2. 写实现 √
 * 3. 检查输入（前缀表达式）的语法正确性,并通过前缀表达式建立表达式二叉树 √
 * 4. 让所有输入以空输入回车结束 √
 * 5. 检查所有容器，在容器内元素被调用前，检查元素数量是否达到 √
 * 6. 把输入改成一整行string和vector<string> √
 * 7. 单独输入变量名,返回其值
 * 8. 单独输入表达式名,要报错 √
 * 9. 为变量名赋值,输入常量表达式
 * 10. 使calt q1 ^22 先构造再计算 √
 * 11. calt q1 ^aa
 * 12. 使calt ^22直接計算且不占用空間(再把build函數細分一下)
 * 13. calt ^22
 * 14. check 用两个子树下标数组代替原有的线性表满二叉树
 * 15. 更新异常发生时的文本信息 √
 *
 */
