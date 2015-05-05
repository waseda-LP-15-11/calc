#include <stdio.h>
#include <math.h>
#include "arithmetic.h"

// doubleの精度が１５桁なのでMAXを１６桁にする
# define MAX 1000000000000000
# define MIN -1000000000000000

double add(double a, double b) {
	if (((a > 0) && (b > (MAX - a))) || ((b < 0) && (a < (MIN - a)))){
		printf("ERROR:: Overflow\n");
		return 0;
	}

	return a + b;
}

double sub(double a, double b) {
	if ((a > 0 && b < MIN + a) || (a < 0 && b > MAX + a)) {
		printf("ERROR:: Overflow\n");
		return 0;
	}
	
	return a - b;
}

double multiple(double a, double b) {
	if (a > 0) {  
		if (b > 0) {  
			if (a > (MAX / b)) {
				printf("ERROR:: Overflow\n");
				return 0;        
			}
    } else { 
			if (b < (MIN / a)) {
				printf("ERROR:: Overflow\n");
				return 0;
			}
		} 
	} else { 
		if (b > 0) {
			if (a < (MIN / b)) {
				printf("ERROR:: Overflow\n");
				return 0;
			}
		} else { 
			if ( (a != 0) && (b < (MAX / a))) {
				printf("ERROR:: Overflow\n");
				return 0;
			}
		}
	}

	return a * b;
}

double divide(double a, double b) {
	if (b == 0) {
		printf("ERROR: Can't divide by 0\n");
		return 0;
	}
	return a / b;
}

double pow_with_check_overflow(double a, double b) {
	if (b > log(MAX)/log(a)) {
		printf("ERROR: Overflow\n");
		return 0;
	}

	return pow(a, b);
}

