#ifndef VALIDDRIVERS_
#define VALIDDRIVERS_
#include <stdbool.h>
#include <glib.h>

typedef struct validdriver *ValidDriver;

ValidDriver create_validdriver(char **fields);

int get_validDriver_id(ValidDriver data) ;

char *get_validDriver_name(ValidDriver data);

int get_validDriver_age(ValidDriver data) ;

char get_validDriver_gender(ValidDriver data);

double get_validDriver_avmedia(ValidDriver data);

double get_validDriver_totalganho(ValidDriver data);

int get_validDriver_nviagens(ValidDriver data);

int get_validDriver_lastride(ValidDriver data);

ValidDriver *get_drivers_list(int tamanho);

void ordenaDrivers(ValidDriver *arr,int l, int r);

void mergeaux2(ValidDriver *arr, int l, int m, int r);

bool isDriver(ValidDriver *drivers, int t_d, char *username,char str[],int show);

void free_arraydrivers(ValidDriver *arr, int t);

#endif