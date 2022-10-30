//
// Created by ling on 2022/10/30.
//

#include "ExpressionManager.h"

ExpressionManager::~ExpressionManager() {
	for(auto &item : trees){

	}
}
void ExpressionManager::setValue(const char name, int val) {
	variable_value[name] = val;
}
void ExpressionManager::setTree(const string & name, ExpressionManager::BinaryTree & tree) {
	trees[name] = tree;
}
int ExpressionManager::getValue(const char name) {
	int val = variable_value[name];
	return val;
}
ExpressionManager::BinaryTree ExpressionManager::getTree(const string &name) {
	auto it = trees.find(name);
	return it == trees.end() ? nullptr : it->second;
}
ExpressionManager::BinaryTree ExpressionManager::getTree(const string &name) const {
	auto it = trees.find(name);
	return it == trees.end() ? nullptr : it->second;
}
void ExpressionManager::welcome() {
	cout << endl << endl << endl << "-Expression Calculator-" << endl
	     << "        -made by linyn" << endl
		 << "How to use:" << endl << endl
		 << ">>> build [name] [expression] // build a expression with name" << endl
		 << ">>> a = 1                     // assign a variable, no expressions applied" << endl
		 << ">>> calt  exp                 // show it's value" << endl
		 << ">>> print exp                 // show v's expression" << endl
		 << ">>> check exp                 // show v's expression as a tree" << endl << endl;
}
void ExpressionManager::perform() {
	try{
        cout <<  ">>> ";
		string input;
		std::getline(cin, input,'\n');
		vector<string> words;
		initInput(words,input); // 以空格和'='为界将input内的东西保存为words
		if(words[0] == "build") {
			build(words);
		}
		else if(words[0] == "print") {
			print(words);
		}
		else if(words[0] == "check"){
			check(words);
		}
		else if(words[0] == "calt"){
			cout << calt(words);
		}
		else{
			assign(words);
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}
void ExpressionManager::initInput(vector<string> &words, string &input) {
	int top{};
	size_t index{};
	while(index < input.size() ){
		words.emplace_back("");
		while(index < input.size() && input[index] != ' ' && input[index] != '='){ words[top] += input[index++];}
		top++;
		if(input[index] == ' '){
			index++;
		}
		else if(input[index] == '='){
			words.emplace_back("");
			words[top++] = input[index++];

		}
	}
}
void ExpressionManager::build(vector<string>& words) {
	string name = words[1];
	string exp = wordsMerge(words,2);
	if(!isOps(exp[0])) { // 首位不是运算符，异常0
		throw std::runtime_error{string{"Error0 of function'build'"}};
	}
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
				throw std::runtime_error{string{"Error2 of function'build'"}};
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
			throw std::runtime_error{string{"Error1 of function'build'"}};
		}
		index++;
	}
	if(!stackNode.empty()){ // 当全部读完后还有运算符没填满，异常！
		throw std::runtime_error{string{"Error3 of function'build'"}};
	}
	setTree(name, tree);             // 把树存起来
}
void ExpressionManager::print(vector<string>& words) const{
	if(words.size() != 2){throw std::runtime_error{string{"Error: Wrong input"}};}
	string name = words[1];
	auto root = getTree(name);
	if (root == nullptr) { // 没有表达式，异常
		throw std::runtime_error{string{"Error: Can't find this expression or variable"}};
	}
	printByMidOrder(root); // 中序打印
}
void ExpressionManager::check(vector<string>& words) const
{
	if(words.size() != 2){throw std::runtime_error{string{"Error: Wrong input"}};}
	string name = words[1];
	auto tree = getTree(name);
	if (tree == nullptr) { // 没有表达式，异常
		throw std::runtime_error{string{"Error: Can't find this expression or variable"}};
	}
	int depth = getDepth(tree);// 获取深度
	printTreelike(tree, depth);// 层序打印
}
int ExpressionManager::calt(vector<string>& words) {
	if(words.size() != 2){throw std::runtime_error{string{"Error: Wrong input"}};}
	string name = words[1];
	auto tree = getTree(name);
	if (tree == nullptr) { // 没有表达式，异常
		throw std::runtime_error{string{"Error: Can't find this expression"}};
	}
	return calculate_tree(tree);
}
string ExpressionManager::wordsMerge(vector<string> &words, int pos = 0) {
	string res ;
	while(pos < words.size()){
		res += words[pos++];
	}
	return res;
}
void ExpressionManager::buildExceptionDeleting(stack<BinaryTree> &stackNode) {
   while(stackNode.size() > 1) {stackNode.pop();}
   if(stackNode.size() == 1) {treeDeleting(stackNode.top()); }
}
void ExpressionManager::printByMidOrder(ExpressionManager::BinaryTree root) const {
    if(root == nullptr) {return ;}
	if(root->left != nullptr) {cout << "(";}
	printByMidOrder(root->left);
	cout << " " << root->val << " ";
	printByMidOrder(root->right);
	if(root->right != nullptr) { cout << ")";}
}
int ExpressionManager::getDepth(ExpressionManager::BinaryTree const root) {
	if(root == nullptr){return 0;}
	int left = getDepth(root->left);
	int right = getDepth(root->right);
	return std::max(left,right) + 1;
}
/* 使用一个数组[2^(depth)-1]记录每层的元素是否存在,有则val无则" "
   并判断"/ \"或"   "
*  空格数：2^(层数-1)-1
       q        7
6     / \
   q   7   q    3
2 / \  5  / \
 q   q 3 q   q  1
/ \ / \1/ \ / \
q q q q q q q q 0
*/void ExpressionManager::printTreelike(ExpressionManager::BinaryTree const root, int depth) {
	if(root == nullptr){return ;}

	int record[1 << depth -1];             // 记录满二叉树中哪些节点有效,哪些无效
	memset(record,0,(1 << depth -1)*sizeof(int)); // 初始化全零
	record[0] = 1; int index = 0;          // 首位初始化为1
	queue<BinaryTree> queueOfWhole;        // 层序遍历的队列实现
	queueOfWhole.push(root);
	while(!queueOfWhole.empty()){
		int n1 = queueOfWhole.size();      // 本层元素个数
		queue<char> queueToPtint;     // 该层结点处理后将其val放入该队列,之后会配合record数组顺序打印
		while(n1--){ // 预处理每一层的节点
			BinaryTree p = queueOfWhole.front(); queueOfWhole.pop();
			queueToPtint.push(p->val);         // 处理时顺便放进打印队列
			if(p->left != nullptr) {queueOfWhole.push(p->left);  record[index << 1] = 1;}
			if(p->right != nullptr) {queueOfWhole.push(p->right);record[index << 1 + 1] = 1;}
		}
		// 打印val
		int n2 = index == 0 ? 1 : index*2;         // 本层满二叉树时元素个数
		int indent1 = 1 << (depth-1) - 1;  // 首val前缩进
		int indent2 = 1 << depth - 1;      // val间缩进
		int i = indent1; while(i--){cout << " ";}  // 首val前缩进
		while(n2--){ // 用来打印
			// 打印val
			if(record[index++] == 1) {cout << queueToPtint.front();queueToPtint.pop();}
			else {cout << " ";}
			// 打印空格
			int n3 = indent2;while(n3--) { cout << " ";}
		}
		cout << endl;
		// 打印"/ \"
		n2 = index == 0 ? 1 : index*2;             // 本层满二叉树时元素个数
		indent1--;
		indent2-=2;
		i = indent1; while(i--){cout << " ";}     // 首"/ \"前缩进
		index-=n2;
		while(n2--){
			// 打印"/ \"
			if(record[index++] == 1) {cout << "/ \\";}
			else {cout << "   ";}
			// 打印空格
			int n3 = indent2;while(n3--) { cout << " ";}
		}
		depth--;
	}
}
bool ExpressionManager::isOps(const char& op) {
	return op == '/' || op == '+' || op == '-' || op == '*' || op == '^' ;
}
int ExpressionManager::calculate_one(char a, char b, char op) {
    int num1 = a - '0';
	int num2 = b - '0';
	int ans = 0;
	switch (op) {
		case '+':
			ans = num1 + num2;
			break;
		case '-':
			ans = num1 - num2;
			break;
		case '*':
		    ans = num1 * num2;
			break;
		case '/':
			ans = num1 / num2;
			break;
		case '^':
			ans = (int)pow(num1, num2);
			break;
		default:
			throw std::runtime_error{string{"Error: wrong op in function'calculate_one'"}};
	}
	return ans;
}
int ExpressionManager::calculate_tree(ExpressionManager::BinaryTree root) {
    if(std::isdigit(root->val)) {return root->val - '0';}
	else if(std::isalpha(root->val)) {return getValue(root->val);}
	else {
		int left = calculate_tree(root->left);
		int right = calculate_tree(root->right);
		return calculate_one(left, right, root->val);
	}
}
void ExpressionManager::assign(vector<string> &words) { // word是单独一个变量名，赋值(目前只支持赋值运算)
	if(words.size() <= 2 || words[0].size() != 1 || words[1] != "="){ // words少于两个或首单词不是char或不是赋值运算,异常
		throw std::runtime_error{string{"Error:Wrong input"}};
	}
	char variable = words[0].front(); // 变量名
	// 整合剩下的words为一个string
	string exp = wordsMerge(words,2);
	// 检查剩下的是否只剩数字了
    for(char c : exp){
		if(!std::isdigit(c)){throw std::runtime_error{string{"Error:Wrong input"}};}
	}
	int num = std::stoi(exp);
	setValue(variable, num);
}
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







