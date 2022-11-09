# P4 表达式类型的实现 实验报告 
**黄鑫21307008**

- [P4 表达式类型的实现 实验报告](#p4-表达式类型的实现-实验报告)
	- [程序功能简要说明](#程序功能简要说明)
			- [一些细节](#一些细节)
	- [程序运行展示](#程序运行展示)
	- [程序运行方式简要说明](#程序运行方式简要说明)
			- [程序执行逻辑](#程序执行逻辑)
	- [部分关键代码及其说明](#部分关键代码及其说明)
	- [TodoList](#todolist)

## 程序功能简要说明

本程序通过clion开发。

本程序没有界面，最佳体验是使用命令行打开程序使用。

~~小黑框才是程序员的浪漫~~

推荐使用方法：
1. 下载后用cmd进入到该文件夹
2. 输入```g++ main.cpp ExpressionManager.cpp -o main.exe```
3. 输入```main```,即可运行

启动后显示信息如下：
```
-Expression Calculator-
              -made by linyn

How to use:
>>> build [name] [expression]                      // build a expression with name
>>> a = 1                                          // assign a variable, no expressions applied
>>> calt  [name]                                   // show it's value
>>> print [name]                                   // show exp's expression
>>> check [name]                                   // show exp's expression as a tree
>>> merge [new_name] [exp1_name] op [exp2_name]    // merge two expresions by a operator
>>> mergeconst [name]                              // merge the const-operation in the expression
>>> quit                                           // quit this program

>>>
```
其中$[name]$表示表达式名或变量名,$[expression]$表示表达式 
主要功能即这7种指令，按照语法输入指令即可。

#### 一些细节
1. 构建的表达式必须要命名，对命名无特别要求，但一定需要用空格隔开
2. 表达式与变量是分开存储的
3. 变量命名必须为单一字母
4. 变量值初始化为0

## 程序运行展示
1. 构建一个表达式(无输出)
```
>>> build a1 ++ a +11 + + 1 +11 a
```
2. 对变量赋值(无输出)
```
>>> a = 4
```
3. 求表达式的值
```
>>> calt a1
13
```
4. 使用calt求值的过程中还能构建表达式，语法同build指令
```
>>> calt a12_sc ^ + *a2 1 - a / 32
729
>>> a =3
>>> calt a12_sc
49
```
5. 将表达式以中缀表达式打印
```
>>> print a1
(( a  + ( 1  +  1 )) + (( 1  + ( 1  +  1 )) +  a ))
```
6. 将表达式以二叉树形式打印
```
>>> check a1
               +
              / \
       +               +
      / \             / \
   a       +       +       a
          / \     / \
         1   1   1   +
                    / \
                    1 1
```
7. 将两个表达式用一个操作符合并起来(无输出)
```
>>> merge 12 a12_sc + a1
>>> check 12
                               +
                              / \
               ^                               +
              / \                             / \
       +               -               +               +
      / \             / \             / \             / \
   *       1       a       /       a       +       +       a
  / \                     / \             / \     / \
 a   2                   3   2           1   1   1   +
                                                    / \
                                                    1 1
```
8. 合并指定表达式中的常数操作（很多细节尚未实现）
```
>>> mergeconst 12
>>> check 12
               +
              / \
       ^               +
      / \             / \
   +       -       +       +
  / \     / \     / \     / \
 *   1   a   1   a   2   3   a
/ \
a 2
```
9. 退出程序
```
>>> quit
```
10. 此外还完善了异常情况
```
>>> build a1 ++ a + 11 + + 1 + 11
Error: Wrong expression of input when calling funciton 'build'
>>> check
Error: Function 'print' except only one parameter.
>>> print q1
Error: Fail to find the expression 'q1' when calling function 'print'.
>>> merge q1 - e2
Error: Wrong input when call function 'merge'.
```

## 程序运行方式简要说明
**头文件**
```
class ExpressionManager {
private:
    // 二叉树结构体
	typedef struct BinaryTreeNode{
		char val;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		explicit BinaryTreeNode(char val = 0) : val(val), left(nullptr), right(nullptr) {}
	}*BinaryTree;

    // 两个容器
	unordered_map<char,int> variable_value;                 // 正在维护的变量值
	unordered_map<string,BinaryTree> trees;                 // 正在维护的二叉树

public:
    // 容器的接口
	~ExpressionManager();                                   // 析构，要拆树
	void setValue(char, int);                               // 设置新的变量值
	void setTree(const string &name, BinaryTree &tree);     // 设置新二叉树
	int getValue(char);                                     // 取出变量值,无则返回0作为初值
	BinaryTree getTree(const string &name);                 // 取出树.无则返回nullptr
	BinaryTree getTree(const string &name) const;           // 取出树.无则返回nullptr

    // 程序主要功能
	static void welcome();                                  // 欢迎语
	bool perform();                                         // 根据用户的输入来确定执行什么操作
	void build(vector<string>& words);                      // 建立前缀表达式二叉树，过程中不求值
	void print(vector<string>& words) const;                // 打印给定二叉树的中序表达式
	void check(vector<string>& words) const;                // 打印给定二叉树的图像
	int calt(vector<string>& words);                        // 求二叉树表达式的值（未知变量初始为0）。不存进变量区
	void merge(vector<string> words);                       // 给定运算符，合并两表达式，获得新名字，不改变原来的两棵树
	void mergeconst(vector<string> words);                  // 将给定二叉树中的能运算的常数运算完成
	void assign(vector<string>& words);                     // 给变量赋值,例: a=1

    // 实现程序主要功能过程的小部件
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
    void calculate_consts(BinaryTree);                       // merge_const.给定一棵二叉树的头结点，将一颗树能做的常数运算完成
};
```

**main函数**
```
#include "ExpressionManager.h"
int main() {
	ExpressionManager manager;
	manager.welcome();
	while(manager.perform());
	return 0;
}
```

#### 程序执行逻辑
1. *perform*是功能的入口，他将返回一个真值来控制main函数中的while循环，实现程序的持续运行或结束（quit指令）
2. *perform*函数内部首先有一个try-catch异常处理语句，所有异常都在此处处理
3. *perform*之后会在终端弹出```>>> ```提示用户上一指令执行成功，请输入后续指令。
4. 用户输入指令后，perform的switch语句将工作，调用相应功能的函数
5. 函数调用成功返回*perform*函数，*perform*函数返回true使*main*中循环语句接着循环；若函数调用时抛出了异常，*perform*处理后依然返回true
6. 若指令为quit，*perform*将返回false，则退出循环，程序结束


## 部分关键代码及其说明
1. check函数：层序遍历打印，其中二叉树的线性表示法，缺点是空间复杂度$O(2^n)$，可以改进。[~~有时间的话~~](#todolist)
```
void ExpressionManager::printTreelike(ExpressionManager::BinaryTree const root, int depth) {
	if(root == nullptr){return ;}

	queue<BinaryTree >queue1;
	::queue<char> toPrint;
	vector<int> record((1<<depth)-1, 0);
	int layer = 0;  // 表示當前層數, root是第0層
	record[0] = 1;
	queue1.push(root);
	while(!queue1.empty() && layer < depth){
		string word ;  // 保存本層輸出
		// 前面空格
		int t = (1 << (depth - layer -1)) -1 ;
		int in = (t << 1) + 1;
		for(int i=0; i<t; i++) { word += " "; }
		// val
		int len = 1 << layer;
		for(int i= 0;i < len && !queue1.empty() ; i++){
			int idx = i+len-1; // record下標,目前位置
			if(record[idx]){
				BinaryTree root = queue1.front(); queue1.pop();
				if(root->left){
					queue1.push(root->left);
					record[((idx+1) << 1) - 1] = 1; // 當前下標*2是左孩子下標;
				}
				if(root->right){
					queue1.push(root->right);
					record[((idx+1) << 1)] = 1; // 當前下標*2再+1是右孩子下標;
				}
				word += root->val;
			}
			else{
				word += " ";
			}
			for(int j = 0; j < in; j++) { word += " "; }
		}
		cout << word << endl;


		word.clear();
		// 前面空格
		t--;
		in = (t << 1) + 1;
		for( int i = 0; i < t; i++) { word += " ";}
		// "/ \"
		for(int i= 0;i < len ;i++){
			int idx = i+len-1; // record下標,目前位置
			if(record[idx]){
				if((((idx+1) << 1) - 1) < ( (1<<depth)-1 ) && record[((idx+1) << 1) - 1]){//判断左子树是否存在
					word += "/";
				} else { word += " "; }
				word += " ";
				if( ((idx+1) << 1) < ( (1<<depth)-1 )  && record[((idx+1) << 1)]){
					word += "\\";
				} else { word += " "; }
			}
			else{
				word += "   ";
			}
			for(int j = 0; j < in; j++) { word += " "; }
		}
		cout << word << endl;
		layer++;
	}
}
```
2. 获得二叉树深度
```
int ExpressionManager::getDepth(ExpressionManager::BinaryTree const root) {
	if(root == nullptr){return 0;}
	int left = getDepth(root->left);
	int right = getDepth(root->right);
	return std::max(left,right) + 1;
}
```
3. 计算一个二叉树表达式的值
```
int ExpressionManager::calculate_tree(ExpressionManager::BinaryTree root) {
    if( std::isdigit(root->val) ) { return root->val - '0'; }
	else if( std::isalpha(root->val) ) { return getValue(root->val); }
	else { // root->val是运算符
		int left = calculate_tree(root->left);
		int right = calculate_tree(root->right);
		return calculate_one(left, right, root->val);
	}
}
```
4. 用于析构与异常处理的拆树
```
void ExpressionManager::treeDeleting(ExpressionManager::BinaryTree root) {
    // 层序拆树
	queue<BinaryTree> queue;
	queue.push(root);
	while(!queue.empty()){
		int n = queue.size();
		while(n--){
			if(queue.front()->left != nullptr){queue.push(queue.front()->left);}
			if(queue.front()->right != nullptr){queue.push(queue.front()->right);}
			delete queue.front();
			queue.pop();
		}
	}
}
```
5. 给定前序表达式构建二叉树，栈实现
```
ExpressionManager::BinaryTree ExpressionManager::buildTree(const string &exp) {
	auto tree = new BinaryTreeNode(exp[0]); // tree是以表达式首运算符构建起来的树
	stack<BinaryTree> stackNode; // 一开始时要把tree放进stack里，参与前缀表达式二叉树的构建
	stackNode.push(tree);
	int index = 1;
	while(index < exp.size()){
		char c = exp[index];
		if(isOps(c)){
			auto a = new BinaryTreeNode(c);
			if(stackNode.empty()){
				stackNode.push(a);
			}
			else if(stackNode.top()->left == nullptr){
				stackNode.top()->left = a;
				stackNode.push(a);
			}
			else {
				stackNode.top()->right = a;
				stackNode.pop();
				stackNode.push(a);
			}
		}
			// 如果是数字或是变量
		else if(std::isdigit(c)|| std::isalpha(c)){
			auto a = new BinaryTreeNode(c);
			if(stackNode.empty()){ // 运算数在运算符之前，异常！
				buildExceptionDeleting(stackNode);// 异常前先拆树
				throw std::runtime_error{string{"Error: Wrong expression of input when calling funciton 'build'"}};
			}
			else if(stackNode.top()->left == nullptr){
				stackNode.top()->left = a;
			}
			else {
				stackNode.top()->right = a;
				stackNode.pop();
			}
		}
		else{ // 不是指定运算符也不是数字或变量，异常！
			buildExceptionDeleting(stackNode);// 异常前先拆树
			throw std::runtime_error{string{"Error: Wrong expression of input when calling funciton 'build'"}};
		}
		index++;
	}
	if(!stackNode.empty()){ // 当全部读完后还有运算符没填满，异常！
		throw std::runtime_error{string{"Error: Wrong expression of input when calling funciton 'build'"}};
	}

	return tree;
}
```

## TodoList
 1. 写头函数 √
 2. 写实现 √
 3. 检查输入（前缀表达式）的语法正确性,并通过前缀表达式建立表达式二叉树 √
 4. 让所有输入以空输入回车结束 √
 5. 检查所有容器，在容器内元素被调用前，检查元素数量是否达到 √
 6. 把输入改成一整行string和vector<string> √
 7. ~~单独输入变量名,返回其值~~ 
 8. 单独输入表达式名,要报错 √
 9. 为变量名赋值,输入常量表达式
 10. 使calt q1 ^22 先构造再计算 √
 11. 使calt ^22直接計算且不占用空間(再把build函數細分一下)
 12. calt ^22
 13. check 用两个子树下标数组代替原有的线性表满二叉树
 14. 更新异常发生时的文本信息 √
