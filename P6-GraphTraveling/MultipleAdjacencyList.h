//
// Created by ling on 2022/11/26.
//

#ifndef P6_GRAPHTRAVELING_MULTIPLEADJACENCYLIST_H
#define P6_GRAPHTRAVELING_MULTIPLEADJACENCYLIST_H
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "myStack.h"
using std::queue;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::map;
using std::string;
/*
(1) 以邻接多重表为存储结构，实现联通无向图的深度优先和广度优先遍历。以指定的结点为起点，分别输出每种遍历下的结点访问序列和相应生成树的边集。
(2) 借助于栈类型（自行定义和实现），用非递归算法实现深度优先遍历。
 */
/* Todo
 * 1. 实现并检查基本算法 √
 * 2. 实现名字与序号的映射 √
 */
template<typename ElemType>
class MultipleAdjacencyList {
private:
	int numVertices{},numEdges{};
	struct EdgeNode{
		int i,j,weight;
		EdgeNode *iLink, *jLink;
		explicit EdgeNode(int i,int j, int weight) : i(i), j(j), weight(weight),  iLink(nullptr), jLink(nullptr) {}
	};
	map<int,ElemType> name2subscript_Map;
	vector<EdgeNode*> mulAdj;
	void printAns(const vector<int>& ansVertex, const vector<EdgeNode*>& ansEdge) const{
		if(ansVertex.size() != numVertices) { cout << endl << "ansVertex.size() goes wrong !!" << endl; }
		if(ansEdge.size() != numVertices-1) { cout << endl << "ansEdge.size() goes wrong !!" << endl; }
//		cout << "Node:  " << ansVertex[0] ;
//		for(int i = 1; i < numVertices; i++){
//			cout << " -> " << ansVertex[i] << "(" << ansEdge[i-1]->weight << ")" ;
//		} cout << endl << endl;
		cout << "city: " << name2subscript_Map.at(ansVertex[0]);
		for(int i = 1; i < numVertices; i++){
			cout << " -> " << name2subscript_Map.at(ansVertex[i]) << "(" << ansEdge[i-1]->weight << ")" ;
		} cout << endl << endl;
	}
	void addEdgeWithoutDirection(int i, int j, int w){
		// 头插法
		auto* e = new EdgeNode(i,j,w);
		if(mulAdj[i] == nullptr) { mulAdj[i] = e; }
		else{
			e->iLink = mulAdj[i];
			mulAdj[i] = e;
		};
		if(mulAdj[j] == nullptr) { mulAdj[j] = e; }
		else{
			e->jLink = mulAdj[j];
			mulAdj[j] = e;
		};
	}
public:
	void setNumVertex(int i) {
		numVertices = i;
		mulAdj.resize(i);
	}
	void setNumEdge(int i) { numEdges = i; }
	[[nodiscard]] int getNumVertex() const { return numVertices; }
	[[nodiscard]] int getNumEdge() const { return numEdges;}
	explicit MultipleAdjacencyList(int v, int e) : numVertices(v), numEdges(e), mulAdj(v, nullptr){}

	MultipleAdjacencyList() = default;
	void createWithoutDirection(const vector<vector<int>>& edges){
		for(const vector<int>& edge : edges){
			int i = edge[0], j = edge[1], w = edge[2];
			addEdgeWithoutDirection(i, j, w);
		}
	}
	void setName(const vector<string>& names){
		int i = 0;
		for(const string& name : names){
			name2subscript_Map[i++] = name;
		}
	}
	void BFSTravel(int i) const{
		if(i < 0 && i >= numVertices) {
			cout << "Invalid input!" << endl;
			return;
		}
		queue<int> queue;          // 存储下标
		vector<bool> visited(numVertices,false);
		vector<int> ansVertex;     // 遍历的结点顺序
		vector<EdgeNode*> ansEdge; // 遍历的边集
		queue.push(i);
		visited[i] = true;
		while(!queue.empty()){
			int a = queue.front(); queue.pop();
			ansVertex.emplace_back(a);
			for(auto *p = mulAdj[a]; p; p = (a == p->i ? p->iLink : p->jLink)){
				int b = (a == p->i ? p->j : p->i);
				if(!visited[b]) {
					ansEdge.emplace_back(p);
					visited[b] = true;
					queue.push(b);
				}
			}
		}
		cout << endl <<  "BFSTravel: " << endl;
		printAns(ansVertex,ansEdge);
	}
	void DFSTravel(int i) const{
		if(i < 0 && i >= numVertices) {
			cout << "Invalid input!" << endl;
			return;
		}
		myStack<int> stack;  // 标记顶点
		vector<bool> visited(numVertices,false); // 标记点是否被遍历过
		vector<int> ansVertex;     // 遍历的结点顺序
		vector<EdgeNode*> ansEdge; // 遍历的边集
		stack.push(i);
		ansVertex.emplace_back(i);
		visited[i] = true;
		while(!stack.empty()){
			int a = stack.top();
			// 遍历a的邻接点，找到最近的有效点。若没有，则从栈中弹出a
			auto * p = mulAdj[a];
			for(; p; p = (a == p->i ? p->iLink : p->jLink)){
				int b = (a == p->i ? p->j : p->i);
				if(!visited[b]){
					stack.push(b);
					visited[b] = true;
					ansVertex.emplace_back(b);
					ansEdge.emplace_back(p);
					break;
				}
			}
			if(p == nullptr) { stack.pop(); }
		}
		cout << "DFSTravel:" << endl;
		printAns(ansVertex,ansEdge);
	}
};


#endif //P6_GRAPHTRAVELING_MULTIPLEADJACENCYLIST_H
