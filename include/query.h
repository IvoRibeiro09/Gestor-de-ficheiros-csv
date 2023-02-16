#ifndef QUERY_
#define QUERY_

#include "parser.h"
#include "rides.h"
#include "queryaux.h"
#include "validDriver.h"
#include "validUser.h"
#include "driverCity.h"


void querie1(char *out, char str[], ValidUser *users, ValidDriver *drivers, int t_u, int t_d, char *username, int show, int ncommand);

void querie2(char *out, char str[], ValidDriver *drivers, int t_d, int n,int show,int ncommand);

void querie3(char *out, char str[], ValidUser *users, int t_u, int n, int show,int ncommand);

void querie4(char *out, char str[], Ride *rides, int t_r, char *city, int show, int ncommand);

void querie5(char *out, char str[], Ride *rides, int t_r, char *data1, char *data2, int show, int ncommand);

void querie6(char *out, char str[], Ride *rides, int t_r, char* city, char *data1, char *data2, int show, int ncommand);

void querie7(char *out, char str[], DriverCity *dc, int t_dc, char *city,int n,int show,int ncommand);

void querie8(char *out, char str[], Ride *rides , int tamanho, char gender,int age, int show,int ncommand, int last);

void querie9(char *out, char str[], Ride *rides , int tamanho, char* data1,char* data2,int show,int ncommand, int last);

#endif