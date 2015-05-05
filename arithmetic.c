#include <float.h>
#include <stdio.h>
#include <math.h>
#include "arithmetic.h"

double add(double a, double b) {
	if (((a > 0) && (b > (DBL_MAX - a))) || ((b < 0) && (a < (DBL_MIN - a)))){
		printf("ERROR:: Overflow\n");
		return 0;
	}

	return a + b;
}

double sub(double a, double b) {
	if ((a > 0 && b < DBL_MIN + a) || (a < 0 && b > DBL_MAX + a)) {
		printf("ERROR:: Overflow\n");
		return 0;
	}
	
	return a - b;
}

double multiple(double a, double b) {
	if (a > 0) {  
		if (b > 0) {  
			if (a > (DBL_MAX / b)) {
				printf("ERROR:: Overflow\n");
				return 0;        
			}
    } else { 
			if (b < (DBL_MIN / a)) {
				printf("ERROR:: Overflow\n");
				return 0;
			}
		} 
	} else { 
		if (b > 0) {
			if (a < (DBL_MIN / b)) {
				printf("ERROR:: Overflow\n");
				return 0;
			}
		} else { 
			if ( (a != 0) && (b < (DBL_MAX / a))) {
				printf("ERROR:: Overflow\n");
				return 0;
			}
		}
	}

	return a * b;
}

double divide(double a, double b) {
	if (b == 0) {
		printf("can't divide by 0\n");
		return 0;
	}
	if (((a == DBL_MIN) && (b == -1))) {
		printf("ERROR: Overflow\n");
		return 0;
	} 

	return a / b;
}

double pow_with_check_overflow(double a, double b) {
	if (b > log(DBL_MAX)/log(a)) {
		printf("ERROR: Overflow\n");
		return 0;
	}

	return pow(a, b);
}

