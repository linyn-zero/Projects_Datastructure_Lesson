#include "calculator.h"

int main() {
	calculator cal;
	cal.welcome();
	while(true){
		cal.perform();
	}
}

/*
 * bug 1: = 6*7^2 �� syntax error  �ѽ������input[i]����Ϊinput[i-1]
 */