#include "ExpressionManager.h"
int main() {
	ExpressionManager manager;
	manager.welcome();
	while(manager.perform());
	return 0;
}
