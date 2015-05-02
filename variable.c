#include <string.h>
#include <stdlib.h>
#include "variable.h"

typedef struct _var_t {
	int value;
	char name[255];
	struct _var_t* less;
	struct _var_t* greater;

} var_t;

static var_t var_tree = {
	NULL,
	{'\0'},
	NULL,
	NULL
};

// 変数の値を表示する
void show_variable(const char* name) {
	int* value = get_value(name);
	if(value != NULL) {
		printf("%s = %d\n", name, *value);
	}
}

// 変数を更新もしくは作成
int update_variable(const char* name, int value) {
	var_t* var = &var_tree;
	var_t** pvar;
	if(var_tree.name[0] == '\0') {
		strcpy(var_tree.name, name);
		var_tree.value = value;
		printf("%s = %d\n", name, value);
		return 0;
	}

	for (pvar = &var; (*pvar) != NULL;) {
		int compare = strcmp(name, (*pvar)->name);
		if(compare == 0) {
			(*pvar)->value = value;
			printf("%s = %d\n", name, value);
			return 0;
		}
		pvar = (compare < 0) ? &(*pvar)->less : &(*pvar)->greater;
	}

	var = (*pvar) = (var_t*)malloc(sizeof(var_t));
	if((*pvar) == NULL) exit(1);

	var->value = value;
	var->less = NULL;
	var->greater = NULL;
	strcpy(var->name, name);
	printf("%s = %d\n", name, value);
	return 0;
}

// 名前がnameの変数を取得する。
int* get_value(const char* name) {
	var_t* var = &var_tree;
	var_t** pvar;

	for (pvar = &var; (*pvar) != NULL;) {
		int compare = strcmp(name, (*pvar)->name);
		if(compare == 0) {
			return &(*pvar)->value;
		}
		pvar = (compare < 0) ? &(*pvar)->less : &(*pvar)->greater;
	}
	printf("ERROR:: '%s' is undefined\n", name );
	return NULL;
}