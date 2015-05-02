#include <string.h>

int add(int v1, int v2){
	if(v1 != 0 && v2 != 0) {
		return v1 + v2;
	}
	return 0;
}
int subtract(int v1, int v2){
	if(v1 != 0 && v2 != 0) {
		return v1 - v2;
	}
	return NULL;
}
int multiply(int v1, int v2){
	if(v1 != NULL && v2 != NULL) {
		return v1 * v2;
	}
	return NULL;
}
int divide(int v1, int v2){
	if(v1 != NULL && v2 != NULL) {
		return v1 / v2;
	}
	return NULL;
}