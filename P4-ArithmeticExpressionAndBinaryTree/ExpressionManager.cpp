//
// Created by ling on 2022/10/30.
//

#include "ExpressionManager.h"

ExpressionManager::~ExpressionManager() {
	for(auto &item : trees){
		treeDeleting(item.second);
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
	cout << endl 
		 << "-Expression Calculator-" << endl
	     << "              -made by linyn" << endl << endl
		 << "How to use:" << endl
		 << ">>> build [name] [expression]                      // build a expression with name" << endl
		 << ">>> a = 1                                          // assign a variable, no expressions applied" << endl
		 << ">>> calt  [name]                                   // show it's value" << endl
		 << ">>> print [name]                                   // show exp's expression" << endl
		 << ">>> check [name]                                   // show exp's expression as a tree" << endl
		 << ">>> merge [new_name] [exp1_name] op [exp2_name]    // merge two expresions by a operator"<< endl
		 << ">>> mergeconst [name]                              // merge the const-operation in the expression"<< endl 
		 << ">>> quit                                           // quit this program" << endl << endl;
}
bool ExpressionManager::perform() {
	try{
        cout << std::setw(4) <<  ">>> ";
		string input;
		std::getline(cin, input,'\n');
		vector<string> words = initInput(input); // 以空格和'='为界将input内的东西保存为words
		if(words.empty()){return true;}
		if(words[0] == "build") {
			build(words);
		}
		else if(words[0] == "print") {
			print(words);
		}
		else if(words[0] == "check"){
			check(words);
		}
		else if(words[0] == "list"){
			list(words);
		}
		else if(words[0] == "calt"){
			cout << calt(words) << endl;
		}
		else if(words[0] == "merge"){
			merge(words);
		}
		else if(words[0] == "mergeconst"){
			mergeconst(words);
		}
		else if(words[0] == "quit"){
			return false;
		}
		else{
			assign(words);
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return true;
}
vector<string> ExpressionManager::initInput(const string &input) {
	vector<string> words;
	size_t index{};
	while(index < input.size() ){
		while(input[index] == ' '){ index++;}
		string word;
		if(input[index] == '='){
			word = input[index++];
		}
		else{
			while(index < input.size() && input[index] != ' ' && input[index] != '='){ word += input[index++];}
		}
		words.emplace_back(word);
	}
	return words;
}
void ExpressionManager::build(vector<string>& words) {
	string name = words[1];
	string exp = wordsMerge(words,2);
	if(!isOps(exp[0])) { // 首位不是运算符，异常0
		throw std::runtime_error{string{"Error: In function 'build', the first char of expression of input isn't operator."}};
	}
	BinaryTree tree = buildTree(exp); // 建樹
	setTree(name, tree);              // 把树存起来
	calculate_tree(tree);        // 检查树的可计算性
}
void ExpressionManager::print(vector<string>& words) const{
	if(words.size() != 2){throw std::runtime_error{string{"Error: Function 'print' except only one parameter."}};}
	string name = words[1];
	auto root = getTree(name);
	if (root == nullptr) { // 没有表达式，异常
		throw std::runtime_error{string{"Error: Fail to find the expression '"+name+"' when calling function 'print'."}};
	}
	printByMidOrder(root); // 中序打印
	cout << endl;
}
void ExpressionManager::check(vector<string>& words) const
{
	if(words.size() != 2){throw std::runtime_error{string{"Error: Function 'print' except only one parameter."}};}
	string name = words[1];
	auto tree = getTree(name);
	if (tree == nullptr) { // 没有表达式，异常
		throw std::runtime_error{string{"Error: Fail to find the expression '"+name+"' when calling function 'check'."}};
	}
	int depth = getDepth(tree);// 获取深度
	printTreelike(tree, depth);// 层序打印
}
int ExpressionManager::calt(vector<string>& words) {
	if(words.size() == 2){
//		if(isOps(words[1].front())){
//			words.insert({})
//		}
//		else{
		string name = words[1];
		auto tree = getTree(name);
		if (tree == nullptr) { // 没有表达式，异常
			throw std::runtime_error{string{"Error: Fail to find the expression '"+name+"' when calling function 'calt'."}};
		}
		return calculate_tree(tree);
//		}
	}
	else if(words.size() > 2){
		string name = words[1];
		build(words);
		return calculate_tree(getTree(name));
	}
	else {throw std::runtime_error{string{"Error: Function 'calt' except more than one parameter."}};}
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
bool ExpressionManager::isOps(const char& op) {
	return op == '/' || op == '+' || op == '-' || op == '*' || op == '^' ;
}
int ExpressionManager::calculate_one(int num1, int num2, char op) {
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
		    if(num2 == 0){
				throw std::runtime_error{string{"Error: Divisor mustn't be 0."}};
			}
			ans = num1 / num2;
			break;
		case '^':
			ans = (int)pow(num1, num2);
			break;
		default:
			throw std::runtime_error{string{"Error: Wrong operator found when calling function 'calculate_one'"}};
	}
	return ans;
}
int ExpressionManager::calculate_tree(ExpressionManager::BinaryTree root) {
    if( std::isdigit(root->val) ) { return root->val - '0'; }
	else if( std::isalpha(root->val) ) { return getValue(root->val); }
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
		if(!std::isdigit(c)){throw std::runtime_error{string{"Error:Wrong input when calling function '[variable_name]=[number]'"}};}
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

void ExpressionManager::merge(vector<string> words) {
    if(words.size() != 5 || words[3].size() != 1 || !isOps(words[3].front()) ){
		throw std::runtime_error{string{"Error: Wrong input when call function 'merge'."}};
	}
	string name = words[1];
	string exp1 = words[2], exp2 = words[4];
	char op = words[3].front();
	BinaryTree tree1 = getTree(exp1), tree2 = getTree(exp2);
	if(tree1 == nullptr){
		throw std::runtime_error{string{"Error: fail to find such express '" +exp1+"'."}};
	}
	if( tree2 == nullptr){
		throw std::runtime_error{string{"Error: fail to find such express '" +exp2+"'."}};
	}
    auto new_tree = new BinaryTreeNode(op);
	new_tree->left = tree1;
	new_tree->right = tree2;
	setTree(name, new_tree);
}

void ExpressionManager::mergeconst(vector<string> words) {
    if(words.size() != 2){
		throw std::runtime_error{string{"Error: Wrong input when call function 'mergeconst'."}};
	}
	string name = words[1];
	BinaryTree tree = getTree(name);
	if(tree == nullptr){
		throw std::runtime_error{string{"Error: Fail to find such express '" +name+"'."}};
	}
	calculate_consts(tree);
}
// root始终是运算符,因此它也总有左右子树
void ExpressionManager::calculate_consts(ExpressionManager::BinaryTree root) {
	if(isOps(root->left->val)){
		calculate_consts(root->left);
	}
	if(isOps(root->right->val)){
		calculate_consts(root->right);
	}
	if(isOps(root->val) && std::isdigit(root->left->val) && std::isdigit(root->right->val)){
		root->val = '0' + calculate_one(root->left->val - '0', root->right->val - '0', root->val);
	    delete root->left;
	    delete root->right;
		root->left = root->right = nullptr;
	}
	else if(isOps(root->val) && ( (std::isdigit(root->left->val) && root->left->val == '0') || (std::isdigit(root->right->val) && root->right->val == '0') ) ) {
		root->val = '0' ;
		delete root->left;
		delete root->right;
		root->left = root->right = nullptr;
	}

}

void ExpressionManager::list(vector<string> &words) const {
	if(words.size() != 2){throw std::runtime_error{string{"Error: Function 'list' except only one parameter."}};}
	string name = words[1];
	auto root = getTree(name);
	if (root == nullptr) { // 没有表达式，异常
		throw std::runtime_error{string{"Error: Fail to find the expression '"+name+"' when calling function 'list'."}};
	}
	printlist(root, 0);
	cout << endl;
}

void ExpressionManager::printlist(ExpressionManager::BinaryTree root, int inteval) const {
    if(!root) { return; }
	int i = inteval;
	while(i--) { cout << " "; }
	cout << root->val << endl;
	printlist(root->left, inteval + 2);
	printlist(root->right, inteval + 2);
}







