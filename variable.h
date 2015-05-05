#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _var_t;
typedef struct _var_t var_t;
void show_variable(const char* name);
int update_variable(const char* name, double value);
double* get_value(const char* name);

#endif