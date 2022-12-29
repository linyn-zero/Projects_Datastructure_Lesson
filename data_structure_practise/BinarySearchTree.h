//
// Created by ling on 2022/11/3.
//

#ifndef DATA_STRUCTURE_PRACTISE_BINARYSEARCHTREE_H
#define DATA_STRUCTURE_PRACTISE_BINARYSEARCHTREE_H
#include <algorithm>
#include <iostream>
#include <string>
#include <exception>
using std::string;
using std::move;
using std::less;
using std::endl;
using std::ostream;
/* From Mark’s book
 * 里面考虑了：
 * 1. 参数是临时变量（则&&），不是临时变量（则const&）
 * 2. 模板
 * 3. pub区
 * 4. pri区
 * 5. root的引用传参
 */

// 因为不会泛式，目前第二个参数只支持std的less<>与greater<>
template <typename Object, typename Comparator=less<Object>> // 默认参数
class BinarySearchTree {
public:
	// 构造与析构
	BinarySearchTree() : root(nullptr) ,isLessThan( Comparator { } ) {}
	BinarySearchTree( const BinarySearchTree & rhs ) : root(nullptr), isLessThan(rhs.isLessThan) {  // rhs: 右值right hand side
		root = clone(rhs.root);
	}
	BinarySearchTree( BinarySearchTree && rhs)  noexcept : root(rhs.root), isLessThan(rhs.isLessThan){
		rhs.root = nullptr;      //  穿别人的鞋，让别人无鞋可穿。
	}

	// 赋值
	BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
		BinarySearchTree copy (rhs); // 调用拷贝构造
		std::swap(copy, *this);
		return *this;
	}
	BinarySearchTree & operator=( BinarySearchTree && rhs) {
		isLessThan = rhs.isLessThan;
		std::swap(root, rhs.root);
		return *this;
	}

	~BinarySearchTree() { clear(); }
	// 查找与打印
	const Object & findMin( ) const {
		if( empty( ) )
			throw std::runtime_error{string{"BinarySearch Tree Overflow!"}};
		return findMin(root)->element;
	}
	const Object & findMax( ) const {
		if( empty( ))
			throw std::runtime_error{string{"BinarySearch Tree Overflow!"}};
		return findMax(root)->element;
	}
	bool contains( const Object & x ) const { return contains(x, root); }
	[[nodiscard]] bool empty() const { return root == nullptr; }

	void printTree( ostream & out = cout) const {
		if( empty( ) )
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}
	// 插入与删除
	void clear() { makeEmpty(root); }
	void remove( const Object & x ) { remove(x, root); }
	void insert( const Object & x) { insert(x, root); }
	void insert(Object && x ) { insert(x, root); }

private:
	// 结点结构体 其实目前还不需要在意它，只要记得我们的类里面有一个root指针即可
    struct BinaryNode{
		Object element;
		BinaryNode *left;
		BinaryNode *right;

		// 构造
		BinaryNode(const Object & theElement, BinaryNode *lt, BinaryNode *rt)
		  : element( theElement ), left( lt ), right( rt ) { }
		BinaryNode(Object && theElement, BinaryNode *lt, BinaryNode *rt)
		  : element( std::move( theElement ) ), left( lt ), right( rt ) { }
	};

	BinaryNode *root;
	Comparator isLessThan;

	// 私有成员函数
	void insert(const Object & x, BinaryNode *& t){
		if(!t) { t = new BinaryNode(x, nullptr, nullptr); }
		else if( isLessThan(x, t->element) ) { insert(x, t->left); }
		else if( isLessThan(t->element, x) ) { insert(x, t->right); }
		else return ; // 已存在,退出函数
//		// 没有迭代写法，因为不能改变t，t是引用传参
	}
	void insert(Object && x, BinaryNode *& t) {
		if(!t) { t = new BinaryNode(move(x), nullptr, nullptr); }
		else if( isLessThan(x, t->element)) { insert( move(x), t->left); }
		else if( isLessThan(t->element, x)) { insert( move(x), t->right);}
		else return;
	}
	void remove(const Object & x, BinaryNode * & t ) {
		if( t == nullptr ) { return ; } // 没这个数，啥都不做
		else if( isLessThan(x, t->element) ) { remove(x, t->left); }
		else if( isLessThan(t->element, x) ) { remove(x, t->right); }
		else if( t->left && t->right ) { // 有两个儿子(本程序默认用右子树的min节点覆盖)
			t->element = findMin(t->right)->element; // 同理致命魔术
			remove(t->element, t->right);
		}
		else { // 一个儿子, 直接删（在没有指针指向它之后
			BinaryNode *oleNode = t;
			t = (t->left ? t->left : t->right);
			delete oleNode;
		} // C语言中，没有引用，我们的函数就要修改成：返回值为结点指针！！
	}
	BinaryNode * findMin(BinaryNode *t) const {
		if(t)
			while(t->left) { t = t->left; } // 这里改变t是安全的
		return t;
//		// 递归写法
//		if( t == nullptr ) { return nullptr;} // 等同于 if( t == nullptr ) { return t; }
//		if( t->left == nullptr ) { return t; }
//		return findMin(x, t->left);
	}
	BinaryNode * findMax(BinaryNode *t) const {
		if(t)
			while(t->right) { t = t->right; }
		return t;
	}
	bool contains(const Object & x, BinaryNode *t ) const {
		if( t == nullptr) { return false; }
		else if( isLessThan(x, t->element) ) { return contains(x, t->left); }
		else if( isLessThan(t->element, x) ) { return contains(x, t->right);}
		else { return true; }
//		// t非引用，安全迭代
//		 while(t){
//			 if( isLessThan(x, t->element) ) { t = t->left; }
//			 else if( isLessThan(t->element, x) ) { t = t->right;}
//			 else { return true; }
//		 }
//		 return false;
	}
	void makeEmpty( BinaryNode * & t) {
		if(t == nullptr) {return;}
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}
	void printTree( BinaryNode *t, std::ostream & out ) const {
		if( t ) {
			printTree(t->left, out );
			out << t->element << " ";
			printTree(t->right, out );
		}
	}
	BinaryNode * clone( BinaryNode *t) const {
		if (t == nullptr) return t;
		else return new BinaryNode ( t->element, clone(t->left), clone(t->right) );
	}
};


#endif //DATA_STRUCTURE_PRACTISE_BINARYSEARCHTREE_H
