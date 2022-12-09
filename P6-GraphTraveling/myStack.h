//
// Created by ling on 2022/11/26.
//

#ifndef P6_GRAPHTRAVELING_MYSTACK_H
#define P6_GRAPHTRAVELING_MYSTACK_H
#define DEFAULT 8
#include <string>
#include <stdexcept>
using std::exception;
using std::string;

template <typename ElemType>
class myStack {
private:
	size_t Capacity;
	int Top; // 始终指向栈顶元素，没有时则指向-1
	ElemType* Container;
    void extend() {
        ElemType * temp = Container;
		Container = nullptr;
	    Capacity *= 2;
	    Container = new ElemType[Capacity];
	    for(size_t i = 0; i <= Top ; i++){
		    Container[i] = temp[i] ;
	    }
	    delete temp;
	}
	bool full() { return (Top + 1) == Capacity; }
public:
	myStack( ) : Capacity(DEFAULT), Top(-1), Container(new ElemType[DEFAULT]) { }
	size_t size() { return Top+1; }
	void push(ElemType x) {
		if(full()){
			extend();
		}
		Container[++Top] = x;
	}
	void pop() { empty() ? throw std::runtime_error{string{"myStack Overflow!"}} : Top--;}
	ElemType& top() { return empty() ? throw std::runtime_error{string{"myStack Overflow!"}} : Container[Top];}
	bool empty() { return Top+1 == 0; }
};


#endif //P6_GRAPHTRAVELING_MYSTACK_H
