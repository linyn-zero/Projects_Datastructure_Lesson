#include "calculator.h"

int main() {
	calculator cal;
	cal.welcome();
	while(true){
		cal.perform();
	}
}

/*
 * bug 1: = 6*7^2 会 syntax error  已解决：将input[i]改正为input[i-1]
 */