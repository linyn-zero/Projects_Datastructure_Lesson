//
// Created by ling on 2022/11/26.
//

#ifndef P6_GRAPHTRAVELING_GRAPHMANAGER_H
#define P6_GRAPHTRAVELING_GRAPHMANAGER_H
#include <iostream>
#include "myStack.h"
#include "MultipleAdjacencyList.h"
#include "AdjacencyList.h"
// ������Ž����û������ͺ���
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
		// ������������
		cout << "Please input the number of vertex and edge:"
		     << endl << ">>> ";
		int v,e; cin >> v >> e;
		// ��������ӳ��
		cout << "Please input the names' map:" << endl
		     << " >>>";
		int t = v;
		vector<string> names;
		while(t--){
			string name; cin >> name;
			names.emplace_back(name);
		}
		// ����߼�
		cout << "Please input the edge set: " << endl
		     << " >>>" ;
		t = e;
		vector<vector<int>> edges;
		while(t--){
			int i,j,w; cin >> i >> j >> w;
			edges.emplace_back(vector<int>({i,j,w}));
		}
		// ��ʼ������
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
		// ��ʼ������
		int startLimit = initialContainer();
		while(true){
			// ʹ�ý���
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
		// ��ӭ��
		cout << "A Program made by linyn." << endl << endl;
	}
	void menu(){
		while(true){
			// ʹ�ý���
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
 * 1. myStack ��
 * 2. ��Ȩ�����ڽӱ� ��
 * 3. ��Ȩ�����ڽӶ��ر� ��
(1) ���ڽӶ��ر�Ϊ�洢�ṹ��ʵ����ͨ����ͼ��������Ⱥ͹�����ȱ�������ָ���Ľ��Ϊ��㣬
 �ֱ����ÿ�ֱ����µĽ��������к���Ӧ�������ı߼��� ��
(2) ������ջ���ͣ����ж����ʵ�֣����÷ǵݹ��㷨ʵ��������ȱ����� ��
(3) ���ڽӱ�Ϊ�洢�ṹ��������������������͹��������������������������������� ��
 * 4. ������ ��
 * 5. �ñ�׼��������
 * 6. �Ż������ʽ

*/

#endif //P6_GRAPHTRAVELING_GRAPHMANAGER_H
