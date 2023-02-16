#ifndef QUERYAUX_
#define QUERYAUX_

#include <stdbool.h>
#include "users.h"
#include "drivers.h"
#include "rides.h"

int dateInt(char* birthstr);

int get_age(int data);

char *get_fullid(int id);

char* dateChar(int date);

char *my_concat(char *s1,char *s2);

#endif