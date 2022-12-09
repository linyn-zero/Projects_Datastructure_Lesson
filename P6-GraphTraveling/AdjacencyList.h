//
// Created by ling on 2022/11/26.
//

#ifndef P6_GRAPHTRAVELING_ADJACENCYLIST_H
#define P6_GRAPHTRAVELING_ADJACENCYLIST_H

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include "myStack.h"
using std::pair;
using std::cout ;
using std::endl;
using std::cin ;
using std::map;
using std::queue;
using std::vector;

/*
(2) 借助于栈类型（自行定义和实现），用非递归算法实现深度优先遍历。
(3) 以邻接表为存储结构，建立深度优先生成树和广度优先生成树，并以树形输出生成树。
 */
/* Todo
 * 1. 实现并检查基本算法 √
 * 2. 实现名字与序号的映射
 */
template <typename ElemType>
class AdjacencyList {
private:
	int numVertex, numEdges;
	// 边表节点
	struct EdgeNode {
		int subscript; // 指向的下标，简单起见用下标表示
		int weight; // 边的权重
		explicit EdgeNode(int s, int w) : subscript(s), weight(w) {}
	};
	void addEdgeWithoutDirection(int i, int j, int w){
		adj[i].emplace_back(EdgeNode (j,w));
		adj[j].emplace_back(EdgeNode (i,w));
	}
public:
	void setNumVertex(int i) {numVertex = i;}
	void setNumEdge(int i) { numEdges = i; }
	[[nodiscard]] const int getNumVertex() const { return numVertex; }
	[[nodiscard]] const int getNumEdge() const { return numEdges;}
	map<int,ElemType> name2subscript_Map; // 元素到下标的映射
	vector<vector<EdgeNode>> adj;
	explicit AdjacencyList(int v, int e) : numVertex(v), numEdges(e), adj(numVertex) {}
	// 只是简单的查看图的内容
	void printList(){
		for(int i = 0;i < numVertex; i++ ){
			std::cout << i << ": ";
			for(EdgeNode p : adj[i] ) {
				std::cout << p.subscript << "(" << p.weight << ") ";
			}
			std::cout << std::endl;
		}
	}
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
	// 建立广度优先生成树，并树型输出（文件目录形式）
	void BFSTree(int i) const{
		queue<int> queue;
		vector<bool> visited(numVertex,false);
		map<int,int> ans;
		queue.push(i);
		visited[i] = true;
		int layer = 0;
		ans[i] = layer;
		while(!queue.empty()){
			layer++;
			int n = queue.size();
			while(n--){
				int a = queue.front(); queue.pop();
				for(const auto &p : adj[a]){
					int i = p.subscript;
					if(!visited[i]){
					    visited[i] = true;
					    ans[i] = layer;
					    queue.push(i);
				    }
				}
			}
		}
		cout << "BFSTree: " << endl;
		myStack<int> stack;
		vector<bool> visited2(numVertex,false);
		stack.push(i);
		visited2[i] = true;
		cout << name2subscript_Map.at(i) << endl;
		while(!stack.empty()){
			int a = stack.top();
			int layer = ans[a] + 1;
			bool flag = true;
			for(const EdgeNode& p : adj[a]){
				int b = p.subscript;
				if(!visited2[b] && ans[b] == layer){
					while(layer--) { cout << "|   ";}
					cout << name2subscript_Map.at(b) << endl;
					stack.push(b);
					visited2[b] = true;
					flag = false;
					break;
				}
			}
			if(flag) {
				stack.pop();
			}
		}
	}
	// 建立深度优先生成树，并树型输出（文件目录形式）
	void DFSTree(int i) const{
		vector<bool> visited(numVertex,false);
		myStack<int> stack;
		vector<pair<int,int>> ans;
		stack.push(i);
		visited[i] = true;
		int layer = 0;
		ans.emplace_back(std::make_pair(i,layer));
		while(!stack.empty()){
			int a = stack.top();
			bool flag = true;
			for(const EdgeNode & p : adj[a]){
				int i = p.subscript;
				if(!visited[i]){
					layer++;
					visited[i] = true;
					stack.push(i);
					ans.emplace_back(std::make_pair(i,layer));
					flag = false;
					break;
				}
			}
			if(flag){
				layer--;
				stack.pop();
			}
		}
		cout << "DFSTree: " << endl;
		if(ans.size() != numVertex) {cout << "ans.size() goes wrong!!!!!" << endl;}
		for(auto [num,layer] : ans){
			while(layer--) { cout << "|   " ;}
			cout << name2subscript_Map.at(num) << endl;
		}
	}
};


#endif //P6_GRAPHTRAVELING_ADJACENCYLIST_H
