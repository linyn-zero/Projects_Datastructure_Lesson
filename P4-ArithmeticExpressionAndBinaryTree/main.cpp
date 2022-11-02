#include "ExpressionManager.h"
int main() {
	ExpressionManager manager;
	manager.welcome();
	while(true){
		manager.perform();
	}
	return 0;
}
