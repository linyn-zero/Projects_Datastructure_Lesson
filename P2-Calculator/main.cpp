#include <iostream>
#include "calculator.h"
#include <queue>


int main() {
	calculator cal;
	cal.welcome();
	while(true){
		cal.perform();
	}
}

/*
 * bug 1: = 6*7^2 »á syntax error
 */