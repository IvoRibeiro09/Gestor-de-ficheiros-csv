#ifndef VALIDUSERS_
#define VALIDUSERS_
#include <glib.h>
#include <stdbool.h>

typedef struct validuser *ValidUser;

ValidUser create_validuser(char **fields);

char* get_validUser_id(ValidUser data);

char *get_validUser_name(ValidUser data) ;

char get_validUser_gender(ValidUser data);

int get_validUser_age(ValidUser data);

int get_validUser_totaldistance(ValidUser data);

double get_validUser_avmedia(ValidUser data);

double get_validUser_totalgasto(ValidUser data);

int get_validUser_nviagens(ValidUser data);

int get_validUser_lastride(ValidUser data);

ValidUser *get_users_list(int tamanho);

void ordenaUsers(ValidUser arr[],int l, int r);

void mergeaux3(ValidUser arr[], int l, int m, int r);

bool isUser(ValidUser *users, int t_u, char *username,char str[],int show);

void free_arrayuser(ValidUser *arr , int t);

#endif