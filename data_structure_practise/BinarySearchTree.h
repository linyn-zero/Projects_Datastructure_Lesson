//
// Created by ling on 2022/11/3.
//

#ifndef DATA_STRUCTURE_PRACTISE_BINARYSEARCHTREE_H
#define DATA_STRUCTURE_PRACTISE_BINARYSEARCHTREE_H
#include "stdlibs.h"
/* From Mark’s book
 * 里面考虑了：
 * 1. 参数是临时变量（则&&），不是临时变量（则const&）
 * 2. 模板
 * 3. pub区
 * 4. pri区
 * 5. root的引用传参
 */
template <typename Comparable>
class BinarySearchTree {
public:
	// 构造与析构
	BinarySearchTree();
	BinarySearchTree( const BinarySearchTree & rhs ) ;// rhs: 右值right hand side
	BinarySearchTree( BinarySearchTree && rhs);
	~BinarySearchTree();

	// 查找与打印
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	bool contains( const Comparable & x ) const;
	bool empty() const;
	void printTree( ostream & out = cout) const;

	// 插入与删除
	void clear();
	void insert( const Comparable & x);
	void insert( Comparable && x );
	void remove( const Comparable & x );

	// 赋值
	BinarySearchTree & operator=( const BinarySearchTree & rhs );
	BinarySearchTree & operator=( BinarySearchTree && rhs);

private:
	// 结点结构体 其实目前还不需要在意它，只要记得我们的类里面有一个root指针即可
    struct BinaryNode{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		// 构造
		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
		  : element( theElement ), left( lt ), right( rt ) { }
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
		  : element( std::move( theElement ) ), left( lt ), right( rt ) { }
	};

	BinaryNode *root;

	// 私有成员函数
};


#endif //DATA_STRUCTURE_PRACTISE_BINARYSEARCHTREE_H
