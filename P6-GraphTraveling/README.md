# P6 ͼ�ı������� ʵ�鱨��
**����21307008**

- [P6 ͼ�ı������� ʵ�鱨��](#p6-ͼ�ı�������-ʵ�鱨��)
  - [�����ܼ�Ҫ˵��](#�����ܼ�Ҫ˵��)
  - [��������չʾ](#��������չʾ)
    - [����ͼ](#����ͼ)
    - [�����ڽӱ�Ĺ�����ȱ���](#�����ڽӱ�Ĺ�����ȱ���)
    - [�����ڽӱ��������ȱ���](#�����ڽӱ��������ȱ���)
    - [�ڽӱ�Ĺ������������](#�ڽӱ�Ĺ������������)
    - [�ڽӱ�Ĺ������������](#�ڽӱ�Ĺ������������-1)
    - [ָ��վ�����̾���](#ָ��վ�����̾���)
  - [�������з�ʽ��Ҫ˵��](#�������з�ʽ��Ҫ˵��)
    - [GraphManager.h](#graphmanagerh)
    - [MultipleAdjacencyList.h](#multipleadjacencylisth)
    - [AdjacencyList.h](#adjacencylisth)
    - [myStack.h](#mystackh)
    - [����ִ���߼�](#����ִ���߼�)
  - [���ֹؼ����뼰��˵��](#���ֹؼ����뼰��˵��)
      - [���ɶ����ڽӱ�](#���ɶ����ڽӱ�)
      - [����һ](#����һ)
      - [���ܶ�](#���ܶ�)
      - [������](#������)
      - [������](#������)
      - [������](#������)


## �����ܼ�Ҫ˵��

������ͨ��clion������


��������ʾ��Ϣ���£�
```
A Program made by linyn.

0. quit
1. create a new Graph.
>>>
```
���� `1`����Կ�ʼ����һ��ͼ��ͼ�����ú�����ʾ��Ϣ���£�
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
�����������ͼ����5�ֲ������ֱ��ǣ�
1. ָ����㣬���ض����ڽӱ�Ĺ�����ȱ����Ľ��������к���Ӧ�������ı߼�
2. ָ����㣬���ض����ڽӱ��������ȱ����Ľ��������к���Ӧ�������ı߼����ǵݹ�ʵ�֣�
3. ָ����㣬�����ڽӱ�Ĺ�������������������������
4. ָ����㣬�����ڽӱ����������������������������
5. ָ����㣬���ص�ͼ����������̾��룬���ṩ·�߲�ѯ���ܡ�

## ��������չʾ
��������Ҫͨ�����-�������û�����
������ֱ����������ͼ��Ϊʾ����
### ����ͼ
```
A Program made by linyn.

0. quit
1. create a new Graph.
>>> 1
Please input the number of vertex and edge:
>>> 25 30
Please input the names' map:
>>> ��³ľ��
����
����
����
���ͺ���
����
���
����
����
����
������
����
֣��
�ɶ�
�人
�Ϻ�
����
����
����
�ϲ�
����
����
����
����
����
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
### �����ڽӱ�Ĺ�����ȱ���
```
>>> 1
Please input start vertex
>>>12

BFSTravel:
city: ֣�� -> �人(534) -> ����(349) -> ����(511) -> ����(695) -> ����(409) -> �Ϻ�(651) -> ���(674) -> �ɶ�(842) -> ����(676) -> ���ͺ���(668) -> ����(675) -> ����(672) -> �ϲ�(367) -> ����(902) -> ����(704) -> ����(1100) -> ����(216) -> ��³ľ��(1892) -> ����(140) -> ����(255) -> ����(622) -> ����(305) -> ����(397) -> ������(242)
```
### �����ڽӱ��������ȱ���
```
>>> 2
Please input start vertex
>>> 23
DFSTravel:
city: ���� -> ����(140) -> ����(675) -> ����(672) -> ����(255) -> ����(607) -> ����(639) -> �ɶ�(1100) -> ����(842) ->֣��(511) -> �人(534) -> ����(349) -> �Ϻ�(651) -> �ϲ�(825) -> ����(622) -> ���(674) -> ����(704) -> ����(305) -> ������(242) -> ����(397) -> ����(137) -> ���ͺ���(668) -> ����(1145) -> ����(216) -> ��³ľ��(1892)
```
### �ڽӱ�Ĺ������������
```
>>>1
 BFSTree:
����
|   ��³ľ��
|   ����
|   ����
|   |   ֣��
|   |   |   ����
|   |   |   |   �Ϻ�
|   |   |   |   |   �ϲ�
|   |   |   |   |   |   ����
|   |   |   �人
|   |   |   |   ����
|   |   |   |   |   ����
|   |   |   |   |   |   ����
|   |   �ɶ�
|   |   |   ����
|   |   |   ����
|   |   |   |   ����
|   |   |   |   |   ����
|   ���ͺ���
|   |   ����
|   |   |   ���
|   |   |   |   ����
|   |   |   |   |   ����
|   |   |   |   |   ����
|   |   |   |   |   |   ������
```
### �ڽӱ�Ĺ������������
```
���
|   ����
|   |   ֣��
|   |   |   ����
|   |   |   |   ����
|   |   |   |   |   ��³ľ��
|   |   |   |   |   ����
|   |   |   |   |   ���ͺ���
|   |   |   |   �ɶ�
|   |   |   |   |   ����
|   |   |   |   |   |   ����
|   |   |   |   |   |   |   ����
|   |   |   |   |   |   |   |   �人
|   |   |   |   |   |   |   |   �ϲ�
|   |   |   |   |   |   |   |   |   �Ϻ�
|   |   |   |   |   |   |   |   |   |   ����
|   |   |   |   |   |   |   |   |   ����
|   |   |   |   |   |   |   |   ����
|   |   |   |   |   |   |   |   |   ����
|   |   |   |   |   |   |   |   ����
|   |   |   |   |   |   |   |   |   ����
|   ����
|   |   ����
|   |   ����
|   |   |   ������
```
### ָ��վ�����̾���
```
>>> 5
Please input start vertex
>>> 22
Dijkstra:
the sorting of the distance from other station:
����(0)
|   ����(255)
|   ����(607)
|   ����(672)
|   |   �ϲ�(1039)
|   |   �人(1081)
|   |   ����(1246)
|   |   ����(1347)
|   |   |   ����(1487)
|   |   �ɶ�(1574)
|   |   |   ֣��(1615)
|   |   |   ����(1661)
|   |   |   �Ϻ�(1864)
|   |   |   |   ����(1964)
|   |   |   |   ����(2126)
|   |   |   |   ����(2310)
|   |   |   |   |   ���(2447)
|   |   |   |   |   ����(2802)
|   |   |   |   |   ���ͺ���(2978)
|   |   |   |   |   |   ����(3018)
|   |   |   |   |   |   ����(3151)
|   |   |   |   |   |   |   ����(3456)
|   |   |   |   |   |   |   ����(3548)
|   |   |   |   |   |   |   |   ������(3698)
|   |   |   |   |   |   ��³ľ��(4694)
Please input a index, then you will get a route:
-1. quit
0. ��³ľ��
1. ����
2. ����
3. ����
4. ���ͺ���
5. ����
6. ���
7. ����
8. ����
9. ����
10. ������
11. ����
12. ֣��
13. �ɶ�
14. �人
15. �Ϻ�
16. ����
17. ����
18. ����
19. �ϲ�
20. ����
21. ����
22. ����
23. ����
24. ����
>>>3
 it's 2126km from ����:
    ����(511) <- ֣��(534) <- �人(409) <- ����(672) <- ����
```



## �������з�ʽ��Ҫ˵��
��������Ҫ��4��ͷ�ļ���ɣ�
### GraphManager.h
```
/* GraphManager.h */
class GraphManager {
private:
	MultipleAdjacencyList<string> mulGraph;  // �����ڽӱ�
	AdjacencyList<string> graph;             // �ڽӱ�
	static int getInteger(int i) ;           // ��ȡָ���С����
	int initialContainer();                  // ����ͼ
	void order();                            // 5�����ܵ����
public:
	GraphManager()= default;                 // ���캯��
	static void welcome();                   // ��ӭ��
	void menu();                             // 01�˵�
};
```
### MultipleAdjacencyList.h
```
/* MultipleAdjacencyList.h */
template<typename ElemType>
class MultipleAdjacencyList {
private:
	int numVertices{},numEdges{};              // ͼ�Ľ���������
	struct EdgeNode{                           // �ߵĽṹ
		int i,j,weight;
		EdgeNode *iLink, *jLink;
		explicit EdgeNode(int i,int j, int weight) : i(i), j(j), weight(weight),  iLink(nullptr), jLink(nullptr) {}
	};
	map<int,ElemType> name2subscript_Map;      // ���������ֵ�ӳ�䣨��ʵ�򵥵�vectorҲ����
	vector<EdgeNode*> mulAdj;                  // �����ڽӱ�
	void printAns(const vector<int>& , const vector<EdgeNode*>& ) const; // ��ӡ��� 
	void addEdgeWithoutDirection(int i, int j, int w); // ���һ���ߣ����ڴ���ͼ�ı߼���
public:
	void setNumVertex(int i) ;                         // ���ý����
 	void setNumEdge(int i);                            // ���ñ���
	[[nodiscard]] int getNumVertex() const ;           // ��ȡ�����
	[[nodiscard]] int getNumEdge() const ;             // ��ȡ����
	
	explicit MultipleAdjacencyList(int v, int e);      // ���캯��
	MultipleAdjacencyList() = default;                 // ���캯��
	void createWithoutDirection(const vector<vector<int>>& ); // ����ͼ�ı߼�
	void setName(const vector<string>& names);         // ���ý�����������ֵ�ӳ��
	
	void BFSTravel(int i) const;                       // ����һ ������ȱ���
	void DFSTravel(int i) const;                       // ���ܶ� ������ȱ���
};
```
### AdjacencyList.h
```
/* AdjacencyList.h */
template <typename ElemType>
class AdjacencyList {
private:
	int numVertex{}, numEdges{};                             // ͼ�Ľ���������
	struct EdgeNode {                                        // �ߵĽṹ
		int subscript;                                       // �������
		int weight;                                          // �ߵ�Ȩ��
		explicit EdgeNode(int s, int w) : subscript(s), weight(w) {}
	};
	map<int,ElemType> name2subscript_Map;                    // ���������ֵ�ӳ�䣨��ʵ�򵥵�vectorҲ����
	vector<vector<EdgeNode>> adj;                            // �ڽӱ�
	void addEdgeWithoutDirection(int i, int j, int w);       // ���һ���ߣ����ڴ���ͼ�ı߼���
	[[nodiscard]] int getWeight(int i, int j) const;         // ��ȡ�ߵ�Ȩ��
	static int getInteger(int i) ;                           // ��ȡָ���С����
public:
	void setNumVertex(int i) ;                               // ���ý����
	void setNumEdge(int i;                                   // ���ñ���
	[[nodiscard]] int getNumVertex() const;                  // ��ȡ�����
	[[nodiscard]] int getNumEdge() const ;                   // ��ȡ����
	
	AdjacencyList() = default;                                // ���캯��
	explicit AdjacencyList(int v, int e) ;                    // ���캯��
	void createWithoutDirection(const vector<vector<int>>& ); // ����ͼ�ı߼�
	void setName(const vector<string>& names);                // ���ý�����������ֵ�ӳ��
	
	void BFSTree(int i) const;   // ������ �������������������������������ļ�Ŀ¼��ʽ��
	void DFSTree(int i) const;   // ������ �������������������������������ļ�Ŀ¼��ʽ��
	void dijkstra(int i) const;  // ������ dijkstra�㷨��������ǰ������վ�������������̾��롣����������ļ�Ŀ¼��ʽ��
};
```
### myStack.h
```
/* myStack.h */
template <typename ElemType>
class myStack {
private:
	size_t Capacity;      // ջ����
	int Top;              // ʼ��ָ��ջ��Ԫ�أ�û��ʱ��ָ��-1
	ElemType* Container;  // ջ�ռ�
	void extend();        // �ռ䲻��ʱ����չ��������չϵ��Ϊ2
	bool full() ;         // �ռ��Ƿ�����
public:
	myStack( ) ;          // ���캯��
	size_t size() ;       // ��������Ԫ�ظ���
	void push(ElemType x);// ����Ԫ��
	void pop() ;          // ����Ԫ��
	ElemType& top() ;     // ����ջ��Ԫ��
	bool empty() ;        // ջ�Ƿ�Ϊ��
};
```

### ����ִ���߼�
1. *welcome*ֻ��һЩ��ӭ�
2. *menu*�ǹ��ܵ���ڣ��Դ�whileѭ����switch��䡣 
   1. ����`1`����*menu*����*order*��
   2. ����`0`���������
3. ����*order*��*order*Ҳ��whileѭ����switch��䡣
   1. ���ȴ���һ��ͼ��
   2. Ȼ������ָ���switch��乤����������Ӧ���ܵĺ�����
   3. ��ָ��Ϊ0������*order*����*menu*��

## ���ֹؼ����뼰��˵��
#### ���ɶ����ڽӱ�
```
void addEdgeWithoutDirection(int i, int j, int w){
    // ͷ�巨
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
#### ����һ
```
void BFSTravel(int i) const{
    if(i < 0 && i >= numVertices) {
        cout << "Invalid input!" << endl;
        return;
    }
    // �ܱ�׼��queueʵ��bfs����׸��
    queue<int> queue;                        // �洢�±�
    vector<bool> visited(numVertices,false); // �����ѷ��ʽ��
    vector<int> ansVertex;                   // �����Ľ��˳��
    vector<EdgeNode*> ansEdge;               // �����ı߼�
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
    printAns(ansVertex,ansEdge);              // ���ó�Ա����������
}
```
#### ���ܶ�
```
void DFSTravel(int i) const{
    if(i < 0 && i >= numVertices) {
        cout << "Invalid input!" << endl;
        return;
    }
    // �ܱ�׼��stackʵ��dfs����׸�������������ȶ����Ż������ǽ��ڹ����巢����㣩
    myStack<int> stack;                      // ��Ƕ���
    vector<bool> visited(numVertices,false); // ��ǵ��Ƿ񱻱�����
    vector<int> ansVertex;                   // �����Ľ��˳��
    vector<EdgeNode*> ansEdge;               // �����ı߼�
    // ��ʼ��
    stack.push(i);
    ansVertex.emplace_back(i);
    visited[i] = true;
    while(!stack.empty()){
        int a = stack.top();
        // ����a���ڽӵ㣬�ҵ��������Ч�㡣��û�У����ջ�е���a
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
    printAns(ansVertex,ansEdge);            // ���ó�Ա����������
}
```
#### ������
```
// �������������������������������ļ�Ŀ¼��ʽ��
void BFSTree(int i) const{
    // һ��BFS����ȡ���������layer��ӳ��
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
    // һ��DFS��ʹ��������layer��ӳ�����BFS�����νṹ
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
#### ������
```
// �������������������������������ļ�Ŀ¼��ʽ��
void DFSTree(int i) const{
 // �ܱ�׼��stackʵ��dfs�����Ǽ�¼��layer
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
#### ������
```
// dijkstra�㷨��������ǰ������վ�������������̾��롣����������ļ�Ŀ¼��ʽ��
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
    priority_queue<Node> d;                  // ʹ�����ȶ����Ż�
    // ��ʼ��
    d.push(Node(i,0,0));
    // ����
    while(true){
        int j(-1),dis = -1,p = -1,l = -1;
        // �ҵ�û�깤�ľ�����С��Ԫ��
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
    
    // �ṩ��һ���Ĺ��� 
    while(true){
        // ����Ŀ�ĵأ���ѯ��·
        cout << "Please input a index, then you will get a route:" << endl;
        cout << "-1. quit" << endl;
        for(auto &[index,name] : name2subscript_Map){
            cout << index << ". " << name << endl;
        } cout << ">>> " ;
        int index = getInteger(getNumVertex()-1);
        if(index == i) { cout << "you are already at " << name2subscript_Map.at(index) << endl; continue;}
        else { cout << "it's " << distance[index] << "km from " << name2subscript_Map.at(index) <<":"<< endl << "    "; }
        
        // ����·��
        while(path[index] != -1){
            int dis = getWeight(index, path[index]);
            cout << name2subscript_Map.at(index) << "(" << dis << ") <- ";
            index = path[index];
        }
        cout << name2subscript_Map.at(index) << endl;
    }
}
```