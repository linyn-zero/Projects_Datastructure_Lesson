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
using std::priority_queue;
using std::vector;

/*
(2) 借助于栈类型（自行定义和实现），用非递归算法实现深度优先遍历。
(3) 以邻接表为存储结构，建立深度优先生成树和广度优先生成树，并以树形输出生成树。
 */
/* Todo
 * 1. 实现并检查基本算法 √
 * 2. 实现名字与序号的映射 √
 * 3. 实现最小生成树
 * 4. 实现最短路径算法 √
 */
template <typename ElemType>
class AdjacencyList {
private:
	int numVertex{}, numEdges{};
	map<int,ElemType> name2subscript_Map; // 元素到下标的映射
	// 边表节点
	struct EdgeNode {
		int subscript; // 指向的下标，简单起见用下标表示
		int weight; // 边的权重
		explicit EdgeNode(int s, int w) : subscript(s), weight(w) {}
	};
	vector<vector<EdgeNode>> adj;
	void addEdgeWithoutDirection(int i, int j, int w){
		adj[i].emplace_back(EdgeNode (j,w));
		adj[j].emplace_back(EdgeNode (i,w));
	}
	[[nodiscard]] int getWeight(int i, int j) const{
		for(const auto& p : adj[i]){
			if(p.subscript == j) {
				return p.weight ;
			}
		}
		return -1;
	}
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
public:
	void setNumVertex(int i) {
		numVertex = i;
		adj.resize(i);
	}
	void setNumEdge(int i) { numEdges = i; }
	[[nodiscard]] int getNumVertex() const { return numVertex; }
	[[nodiscard]] int getNumEdge() const { return numEdges;}
	AdjacencyList() = default;
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
		queue<int> queueBFS;
		vector<bool> visited(numVertex,false);
		map<int,int> ans;
		queueBFS.push(i);
		visited[i] = true;
		int layer = 0;
		ans[i] = layer;
		while(!queueBFS.empty()){
			layer++;
			size_t n = queueBFS.size();
			while(n--){
				int a = queueBFS.front(); queueBFS.pop();
				for(const auto &p : adj[a]){
					int b = p.subscript;
					if(!visited[b]){
					    visited[b] = true;
					    ans[b] = layer;
					    queueBFS.push(b);
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
			int l = ans[a] + 1;
			bool flag = true;
			for(const EdgeNode& p : adj[a]){
				int b = p.subscript;
				if(!visited2[b] && ans[b] == l){
					while(l--) { cout << "|   ";}
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
				int b = p.subscript;
				if(!visited[b]){
					layer++;
					visited[b] = true;
					stack.push(b);
					ans.emplace_back(std::make_pair(b, layer));
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
		for(auto [num,l] : ans){
			while(l--) { cout << "|   " ;}
			cout << name2subscript_Map.at(num) << endl;
		}
	}
	// dijkstra算法，并生成前往各个站点的生成树与最短距离。树型输出（文件目录形式）
	void dijkstra(int i) const{
		cout << "Dijkstra: " << endl
		     << "the sorting of the distance from other station:" << endl;
		struct Node{
			int key, d, layer, path;
			explicit Node(int k, int d, int l, int p = -1) : key(k), d(d), layer(l), path(p){}
			bool operator< (const Node& o) const { return d > o.d; }
		};
		vector<bool> final(numVertex,false);
		vector<int> distance(numVertex,INT_MAX);
		vector<int> path(numVertex,-1);
		priority_queue<Node> d;
		// 初始化
		d.push(Node(i,0,0));
		// 遍历
		while(true){
			int j(-1),dis = -1,p = -1,l = -1;
			// 找到没完工的距离最小的元素
			while(!d.empty()){
				Node a = d.top(); d.pop();
				if(!final[a.key]){
					j = a.key;
					dis = a.d;
					p = a.path;
					l = a.layer;
					break;
				}
			}
			if(j == -1){ break; }
			final[j] = true;
			distance[j] = dis;
			path[j] = p;
			int layer = l;
			while(layer--) { cout << "|   " ;}
			cout << name2subscript_Map.at(j) << "(" << dis << ")" << endl;
			for(auto& edge : adj[j]){
				if(!final[edge.subscript] ){
					d.push(Node(edge.subscript, edge.weight + dis, l + 1, j));
				}
			}
		}
		while(true){
			// 输入目的地，查询线路
			cout << "Please input a index, then you will get a route:" << endl;
			cout << "0. quit" << endl;
			for(auto &[index,name] : name2subscript_Map){
				cout << index+1 << ". " << name << endl;
			} cout << ">>> " ;
			int index = getInteger(getNumVertex());
			if(index == 0) {return;}
			index--;
			if(index == i) { cout << "you are already at " << name2subscript_Map.at(index) << endl; continue;}
			else { cout << "it's " << distance[index] << "km from " << name2subscript_Map.at(index) <<":"<< endl << "    "; }
			// 回溯路径
			while(path[index] != -1){
				int dis = getWeight(index, path[index]);
				cout << name2subscript_Map.at(index) << "(" << dis << ") <- ";
				index = path[index];
			}
			cout << name2subscript_Map.at(index) << endl;
		}
	}
};


#endif //P6_GRAPHTRAVELING_ADJACENCYLIST_H
