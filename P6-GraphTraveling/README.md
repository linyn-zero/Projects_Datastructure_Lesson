# P6 图的遍历程序 实验报告
**黄鑫21307008**

- [P6 图的遍历程序 实验报告](#p6-图的遍历程序-实验报告)
  - [程序功能简要说明](#程序功能简要说明)
  - [程序运行展示](#程序运行展示)
    - [创建图](#创建图)
    - [多重邻接表的广度优先遍历](#多重邻接表的广度优先遍历)
    - [多重邻接表的深度优先遍历](#多重邻接表的深度优先遍历)
    - [邻接表的广度优先生成树](#邻接表的广度优先生成树)
    - [邻接表的广度优先生成树](#邻接表的广度优先生成树-1)
    - [指定站点的最短距离](#指定站点的最短距离)
  - [程序运行方式简要说明](#程序运行方式简要说明)
    - [GraphManager.h](#graphmanagerh)
    - [MultipleAdjacencyList.h](#multipleadjacencylisth)
    - [AdjacencyList.h](#adjacencylisth)
    - [myStack.h](#mystackh)
    - [程序执行逻辑](#程序执行逻辑)
  - [部分关键代码及其说明](#部分关键代码及其说明)
      - [生成多重邻接表](#生成多重邻接表)
      - [功能一](#功能一)
      - [功能二](#功能二)
      - [功能三](#功能三)
      - [功能四](#功能四)
      - [功能五](#功能五)


## 程序功能简要说明

本程序通过clion开发。


启动后显示信息如下：
```
A Program made by linyn.

0. quit
1. create a new Graph.
>>>
```
输入 `1`后可以开始创建一个图。图创建好后便会显示信息如下：
```
What would you like to do with this Graph:
1. MultipleAdjacencyList's BFSTravel
2. MultipleAdjacencyList's DFSTravel
3. AdjacencyList's BFSTree
4. AdjacencyList's DFSTravel
5. Dijkstra
0. quit
>>>
```
本程序允许对图进行5种操作，分别是：
1. 指定起点，返回多重邻接表的广度优先遍历的结点访问序列和相应生成树的边集
2. 指定起点，返回多重邻接表的深度优先遍历的结点访问序列和相应生成树的边集（非递归实现）
3. 指定起点，返回邻接表的广度优先生成树，以树型输出。
4. 指定起点，返回邻接表的深度优先生成树，以树型输出。
5. 指定起点，返回到图上其余点的最短距离，并提供路线查询功能。

## 程序运行展示
本程序主要通过序号-功能与用户交互
，下面直接用所给地图作为示例：
### 创建图
```
A Program made by linyn.

0. quit
1. create a new Graph.
>>> 1
Please input the number of vertex and edge:
>>> 25 30
Please input the names' map:
>>> 乌鲁木齐
兰州
西宁
西安
呼和浩特
北京
天津
沈阳
大连
长春
哈尔滨
徐州
郑州
成都
武汉
上海
昆明
贵阳
株洲
南昌
福州
南宁
柳州
广州
深圳
Please input the edge set:
>>> 
0 1 1892 
1 2 216 
1 3 676
5 6 137
6 7 704

7 8 397
7 9 305
9 10 242
5 12 695
3 12 511

11 12 349
4 5 668 
1 4 1145
6 11 674
3 13 842

12 14 534
11 15 651
15 19 825
14 18 409
13 16 1100

13 17 967
16 17 639
17 18 902
18 19 367
19 20 622

17 22 607
18 22 672
22 21 255
18 23 675
23 24 140
```
### 多重邻接表的广度优先遍历
```
>>> 1
Please input start vertex
>>>12

BFSTravel:
city: 郑州 -> 武汉(534) -> 徐州(349) -> 西安(511) -> 北京(695) -> 株洲(409) -> 上海(651) -> 天津(674) -> 成都(842) -> 兰州(676) -> 呼和浩特(668) -> 广州(675) -> 柳州(672) -> 南昌(367) -> 贵阳(902) -> 沈阳(704) -> 昆明(1100) -> 西宁(216) -> 乌鲁木齐(1892) -> 深圳(140) -> 南宁(255) -> 福州(622) -> 长春(305) -> 大连(397) -> 哈尔滨(242)
```
### 多重邻接表的深度优先遍历
```
>>> 2
Please input start vertex
>>> 23
DFSTravel:
city: 广州 -> 深圳(140) -> 株洲(675) -> 柳州(672) -> 南宁(255) -> 贵阳(607) -> 昆明(639) -> 成都(1100) -> 西安(842) ->郑州(511) -> 武汉(534) -> 徐州(349) -> 上海(651) -> 南昌(825) -> 福州(622) -> 天津(674) -> 沈阳(704) -> 长春(305) -> 哈尔滨(242) -> 大连(397) -> 北京(137) -> 呼和浩特(668) -> 兰州(1145) -> 西宁(216) -> 乌鲁木齐(1892)
```
### 邻接表的广度优先生成树
```
>>>1
 BFSTree:
兰州
|   乌鲁木齐
|   西宁
|   西安
|   |   郑州
|   |   |   徐州
|   |   |   |   上海
|   |   |   |   |   南昌
|   |   |   |   |   |   福州
|   |   |   武汉
|   |   |   |   株洲
|   |   |   |   |   广州
|   |   |   |   |   |   深圳
|   |   成都
|   |   |   昆明
|   |   |   贵阳
|   |   |   |   柳州
|   |   |   |   |   南宁
|   呼和浩特
|   |   北京
|   |   |   天津
|   |   |   |   沈阳
|   |   |   |   |   大连
|   |   |   |   |   长春
|   |   |   |   |   |   哈尔滨
```
### 邻接表的广度优先生成树
```
天津
|   北京
|   |   郑州
|   |   |   西安
|   |   |   |   兰州
|   |   |   |   |   乌鲁木齐
|   |   |   |   |   西宁
|   |   |   |   |   呼和浩特
|   |   |   |   成都
|   |   |   |   |   昆明
|   |   |   |   |   |   贵阳
|   |   |   |   |   |   |   株洲
|   |   |   |   |   |   |   |   武汉
|   |   |   |   |   |   |   |   南昌
|   |   |   |   |   |   |   |   |   上海
|   |   |   |   |   |   |   |   |   |   徐州
|   |   |   |   |   |   |   |   |   福州
|   |   |   |   |   |   |   |   柳州
|   |   |   |   |   |   |   |   |   南宁
|   |   |   |   |   |   |   |   广州
|   |   |   |   |   |   |   |   |   深圳
|   沈阳
|   |   大连
|   |   长春
|   |   |   哈尔滨
```
### 指定站点的最短距离
```
>>> 5
Please input start vertex
>>> 22
Dijkstra:
the sorting of the distance from other station:
柳州(0)
|   南宁(255)
|   贵阳(607)
|   株洲(672)
|   |   南昌(1039)
|   |   武汉(1081)
|   |   昆明(1246)
|   |   广州(1347)
|   |   |   深圳(1487)
|   |   成都(1574)
|   |   |   郑州(1615)
|   |   |   福州(1661)
|   |   |   上海(1864)
|   |   |   |   徐州(1964)
|   |   |   |   西安(2126)
|   |   |   |   北京(2310)
|   |   |   |   |   天津(2447)
|   |   |   |   |   兰州(2802)
|   |   |   |   |   呼和浩特(2978)
|   |   |   |   |   |   西宁(3018)
|   |   |   |   |   |   沈阳(3151)
|   |   |   |   |   |   |   长春(3456)
|   |   |   |   |   |   |   大连(3548)
|   |   |   |   |   |   |   |   哈尔滨(3698)
|   |   |   |   |   |   乌鲁木齐(4694)
Please input a index, then you will get a route:
-1. quit
0. 乌鲁木齐
1. 兰州
2. 西宁
3. 西安
4. 呼和浩特
5. 北京
6. 天津
7. 沈阳
8. 大连
9. 长春
10. 哈尔滨
11. 徐州
12. 郑州
13. 成都
14. 武汉
15. 上海
16. 昆明
17. 贵阳
18. 株洲
19. 南昌
20. 福州
21. 南宁
22. 柳州
23. 广州
24. 深圳
>>>3
 it's 2126km from 西安:
    西安(511) <- 郑州(534) <- 武汉(409) <- 株洲(672) <- 柳州
```



## 程序运行方式简要说明
本程序主要由4个头文件组成：
### GraphManager.h
```
/* GraphManager.h */
class GraphManager {
private:
	MultipleAdjacencyList<string> mulGraph;  // 多重邻接表
	AdjacencyList<string> graph;             // 邻接表
	static int getInteger(int i) ;           // 读取指令的小函数
	int initialContainer();                  // 创建图
	void order();                            // 5个功能的入口
public:
	GraphManager()= default;                 // 构造函数
	static void welcome();                   // 欢迎语
	void menu();                             // 01菜单
};
```
### MultipleAdjacencyList.h
```
/* MultipleAdjacencyList.h */
template<typename ElemType>
class MultipleAdjacencyList {
private:
	int numVertices{},numEdges{};              // 图的结点数与边数
	struct EdgeNode{                           // 边的结构
		int i,j,weight;
		EdgeNode *iLink, *jLink;
		explicit EdgeNode(int i,int j, int weight) : i(i), j(j), weight(weight),  iLink(nullptr), jLink(nullptr) {}
	};
	map<int,ElemType> name2subscript_Map;      // 索引与名字的映射（其实简单的vector也可以
	vector<EdgeNode*> mulAdj;                  // 多重邻接表
	void printAns(const vector<int>& , const vector<EdgeNode*>& ) const; // 打印输出 
	void addEdgeWithoutDirection(int i, int j, int w); // 添加一条边（用于创建图的边集）
public:
	void setNumVertex(int i) ;                         // 设置结点数
 	void setNumEdge(int i);                            // 设置边数
	[[nodiscard]] int getNumVertex() const ;           // 获取结点数
	[[nodiscard]] int getNumEdge() const ;             // 获取边数
	
	explicit MultipleAdjacencyList(int v, int e);      // 构造函数
	MultipleAdjacencyList() = default;                 // 构造函数
	void createWithoutDirection(const vector<vector<int>>& ); // 创建图的边集
	void setName(const vector<string>& names);         // 设置结点索引与名字的映射
	
	void BFSTravel(int i) const;                       // 功能一 广度优先遍历
	void DFSTravel(int i) const;                       // 功能二 深度优先遍历
};
```
### AdjacencyList.h
```
/* AdjacencyList.h */
template <typename ElemType>
class AdjacencyList {
private:
	int numVertex{}, numEdges{};                             // 图的结点数与边数
	struct EdgeNode {                                        // 边的结构
		int subscript;                                       // 结点索引
		int weight;                                          // 边的权重
		explicit EdgeNode(int s, int w) : subscript(s), weight(w) {}
	};
	map<int,ElemType> name2subscript_Map;                    // 索引与名字的映射（其实简单的vector也可以
	vector<vector<EdgeNode>> adj;                            // 邻接表
	void addEdgeWithoutDirection(int i, int j, int w);       // 添加一条边（用于创建图的边集）
	[[nodiscard]] int getWeight(int i, int j) const;         // 获取边的权重
	static int getInteger(int i) ;                           // 读取指令的小函数
public:
	void setNumVertex(int i) ;                               // 设置结点数
	void setNumEdge(int i;                                   // 设置边数
	[[nodiscard]] int getNumVertex() const;                  // 获取结点数
	[[nodiscard]] int getNumEdge() const ;                   // 获取边数
	
	AdjacencyList() = default;                                // 构造函数
	explicit AdjacencyList(int v, int e) ;                    // 构造函数
	void createWithoutDirection(const vector<vector<int>>& ); // 创建图的边集
	void setName(const vector<string>& names);                // 设置结点索引与名字的映射
	
	void BFSTree(int i) const;   // 功能三 建立广度优先生成树，并树型输出（文件目录形式）
	void DFSTree(int i) const;   // 功能四 建立深度优先生成树，并树型输出（文件目录形式）
	void dijkstra(int i) const;  // 功能五 dijkstra算法，并生成前往各个站点的生成树与最短距离。树型输出（文件目录形式）
};
```
### myStack.h
```
/* myStack.h */
template <typename ElemType>
class myStack {
private:
	size_t Capacity;      // 栈容量
	int Top;              // 始终指向栈顶元素，没有时则指向-1
	ElemType* Container;  // 栈空间
	void extend();        // 空间不足时的拓展函数，拓展系数为2
	bool full() ;         // 空间是否已满
public:
	myStack( ) ;          // 构造函数
	size_t size() ;       // 返回已有元素个数
	void push(ElemType x);// 加入元素
	void pop() ;          // 弹出元素
	ElemType& top() ;     // 返回栈顶元素
	bool empty() ;        // 栈是否为空
};
```

### 程序执行逻辑
1. *welcome*只是一些欢迎语。
2. *menu*是功能的入口，自带while循环与switch语句。 
   1. 输入`1`将从*menu*进入*order*；
   2. 输入`0`程序结束。
3. 进入*order*。*order*也有while循环与switch语句。
   1. 首先创建一个图。
   2. 然后输入指令，让switch语句工作，调用相应功能的函数。
   3. 若指令为0，将从*order*返回*menu*。

## 部分关键代码及其说明
#### 生成多重邻接表
```
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
```
#### 功能一
```
void BFSTravel(int i) const{
    if(i < 0 && i >= numVertices) {
        cout << "Invalid input!" << endl;
        return;
    }
    // 很标准的queue实现bfs，不赘述
    queue<int> queue;                        // 存储下标
    vector<bool> visited(numVertices,false); // 保存已访问结点
    vector<int> ansVertex;                   // 遍历的结点顺序
    vector<EdgeNode*> ansEdge;               // 遍历的边集
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
    printAns(ansVertex,ansEdge);              // 调用成员函数输出结果
}
```
#### 功能二
```
void DFSTravel(int i) const{
    if(i < 0 && i >= numVertices) {
        cout << "Invalid input!" << endl;
        return;
    }
    // 很标准的stack实现dfs，不赘述（可以用优先队列优化，我们将在功能五发现这点）
    myStack<int> stack;                      // 标记顶点
    vector<bool> visited(numVertices,false); // 标记点是否被遍历过
    vector<int> ansVertex;                   // 遍历的结点顺序
    vector<EdgeNode*> ansEdge;               // 遍历的边集
    // 初始化
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
    printAns(ansVertex,ansEdge);            // 调用成员函数输出结果
}
```
#### 功能三
```
// 建立广度优先生成树，并树型输出（文件目录形式）
void BFSTree(int i) const{
    // 一次BFS，获取索引与层数layer的映射
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
    // 一次DFS，使用索引与layer的映射输出BFS的树形结构
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
        if(flag) { stack.pop(); }
    }
}
```
#### 功能四
```
// 建立深度优先生成树，并树型输出（文件目录形式）
void DFSTree(int i) const{
 // 很标准的stack实现dfs，但是记录了layer
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
```
#### 功能五
```
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
    priority_queue<Node> d;                  // 使用优先队列优化
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
    
    // 提供进一步的功能 
    while(true){
        // 输入目的地，查询线路
        cout << "Please input a index, then you will get a route:" << endl;
        cout << "-1. quit" << endl;
        for(auto &[index,name] : name2subscript_Map){
            cout << index << ". " << name << endl;
        } cout << ">>> " ;
        int index = getInteger(getNumVertex()-1);
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
```