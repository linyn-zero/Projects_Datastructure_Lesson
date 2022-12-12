//
// Created by ling on 2022/11/26.
//

#ifndef P6_GRAPHTRAVELING_GRAPHMANAGER_H
#define P6_GRAPHTRAVELING_GRAPHMANAGER_H
#include <iostream>
#include "myStack.h"
#include "MultipleAdjacencyList.h"
#include "AdjacencyList.h"
// 简单用序号进行用户交互就好了
class GraphManager {
private:
	MultipleAdjacencyList<string> mulGraph;
	AdjacencyList<string> graph;
	static int getInteger(int i) {
		string input;
		cin >> input;
		while(!std::isdigit(input[0])){
			cout << "Wrong input;" << endl
			     << "Try again?" << endl
			     << ">>> ";
			cin >> input;
		}
		int res = std::stoi(input);
		while(res < 0 || res > i){
			cout << "Wrong input;" << endl
			     << "Try again?" << endl
			     << ">>> ";
			cin >> input;
			res = std::stoi(input);
		}
		return res;
	}
	int initialContainer(){
		// 输入点数与边数
		cout << "Please input the number of vertex and edge:"
		     << endl << ">>> ";
		int v,e; cin >> v >> e;
		// 输入名字映射
		cout << "Please input the names' map:" << endl
		     << " >>>";
		int t = v;
		vector<string> names;
		while(t--){
			string name; cin >> name;
			names.emplace_back(name);
		}
		// 输入边集
		cout << "Please input the edge set: " << endl
		     << " >>>" ;
		t = e;
		vector<vector<int>> edges;
		while(t--){
			int i,j,w; cin >> i >> j >> w;
			edges.emplace_back(vector<int>({i,j,w}));
		}
		// 初始化两者
		mulGraph.setNumVertex(v);
		mulGraph.setNumEdge(e);
		mulGraph.setName(names);
		mulGraph.createWithoutDirection(edges);
		graph.setNumVertex(v);
		graph.setNumEdge(v);
		graph.setName(names);
		graph.createWithoutDirection(edges);
		return v;
	}
	void order(){
		// 初始化容器
		int startLimit = initialContainer();
		while(true){
			// 使用介绍
			cout << "What would you like to do with this Graph: " << std::endl
			     << "1. MultipleAdjacencyList's BFSTravel" << std::endl
			     << "2. MultipleAdjacencyList's DFSTravel" << std::endl
			     << "3. AdjacencyList's BFSTree" << std::endl
			     << "4. AdjacencyList's DFSTree" << endl
				 << "5. Dijkstra" << endl
			     << "0. quit" << endl
			     << ">>> " ;
			int command = getInteger(5);
			int start ;
			switch (command) {
				case 0:
					return;
				case 1:
					cout << "Please input start vertex" << endl << ">>> ";
					start = getInteger(startLimit);
					mulGraph.BFSTravel(start);
					break;
				case 2:
					cout << "Please input start vertex" << endl << ">>> ";
					start = getInteger(startLimit);
					mulGraph.DFSTravel(start);
					break;
				case 3:
					cout << "Please input start vertex" << endl << ">>> ";
					start = getInteger(startLimit);
					graph.BFSTree(start);
					break;
				case 4:
					cout << "Please input start vertex" << endl << ">>> ";
					start = getInteger(startLimit);
					graph.DFSTree(start);
					break;
				case 5:
					cout << "Please input start vertex" << endl << ">>> ";
					start = getInteger(startLimit);
					graph.dijkstra(start);
					break;
			}
		}
	}
public:
	GraphManager()= default;
	static void welcome(){
		// 欢迎语
		cout << "A Program made by linyn." << endl << endl;
	}
	void menu(){
		while(true){
			// 使用介绍
			cout << "0. quit" << endl
			     << "1. create a new Graph." << endl
			     << ">>> ";
			int command = getInteger(1);
			switch (command) {
				case 0:
					return;
				case 1:
					order();
					break;
			}
		}
	}
};

/**
 * TODo
 * 1. myStack √
 * 2. 有权无向邻接表 √
 * 3. 有权无向邻接多重表 √
(1) 以邻接多重表为存储结构，实现联通无向图的深度优先和广度优先遍历。以指定的结点为起点，
 分别输出每种遍历下的结点访问序列和相应生成树的边集。 √
(2) 借助于栈类型（自行定义和实现），用非递归算法实现深度优先遍历。 √
(3) 以邻接表为存储结构，建立深度优先生成树和广度优先生成树，并以树形输出生成树。 √
 * 4. 管理器 √
 * 5. 用标准样例测试
 * 6. 优化输出格式

*/

#endif //P6_GRAPHTRAVELING_GRAPHMANAGER_H
