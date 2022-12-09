//
// Created by ling on 2022/12/9.
//

#ifndef P6_GRAPHTRAVELING_TEST_H
#define P6_GRAPHTRAVELING_TEST_H
#include <iostream>
#include "myStack.h"
#include "MultipleAdjacencyList.h"
#include "AdjacencyList.h"
using std::cin;
using std::cout;
void test_myStack(){
	myStack<int> a;
	int t ; cin >> t;
	int x = 1;
	while(t--){
		int command; cin >> command;
		if(command == 1) a.push(x++);
		else { cout << a.top() << " "; a.pop();}
	}
	while(!a.empty()) { cout << a.top() << " "; a.pop();}
}
void test_new(){
	int* a = new int[10];
	for(int i = 0; i < 10; i++){
		a[i] = i;
	}
	for(int i = 0; i < 10; i++){
		cout << a[i] << " ";
	}
	int* temp = a;
	for(int i = 0; i < 10; i++){
		cout << temp[i] << " ";
	}
	a = new int[20];
	for(int i =0 ;i < 10; i++){
		a[i] = temp[i];
	}
	for(int i = 10; i < 20; i++){
		a[i] = i;
	}
	for(int i = 0; i < 20; i++){
		cout << a[i] << " ";
	}
}
void test_MultipleAdjacencyList(){
	MultipleAdjacencyList<string> a(7,9);
	a.setName();
	a.createWithoutDirection();
	for(int i = 0; i < 7; i++){
		a.BFSTravel(i);
	}
	for(int i = 0; i < 7; i++){
		a.DFSTravel(i);
	}
	/*
0 1 1
0 2 2
0 5 5
1 3 3
1 5 5
1 6 6
2 5 5
3 4 4
4 5 5
	 *
	 */
}
void test_AdjacencyList(){
	AdjacencyList<string> a(7,9);
	a.setName();
	a.createWithoutDirection();
	a.printList();

	for(int i = 0; i < 7; i++){
		a.BFSTree(i);
	}
	for(int i = 0; i < 7; i++){
		a.DFSTree(i);
	}
}
#endif //P6_GRAPHTRAVELING_TEST_H
