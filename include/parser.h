#ifndef PARSER_
#define PARSER_
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "query.h"
#include "queryaux.h"
#include "driver_ride.h"
#include "validDriver.h"
#include <stdbool.h>

void get_fields(char *line, char** fields);

int verifyDate(char *str,char year[],char month[],char day[]);

int onlyDigitsDate(char *aux);

int verifyCarClass(char *class);

void toLower(char *str, int n);

int verifyAccountStatus(char *status);

int onlyDigits(char *aux);

int verifyInt(char *dis);

int onlyDigitsDouble(char *aux);

int verifyIntdecimal(char *num);

void parser_users(Cat_Users cat_users, char* path);

void parser_drivers(Cat_Drivers cat_drivers, char* path);

int new_rides(Cat_Users cat_users, Cat_Drivers cat_drivers,Cat_Driver_Ride cdr, char* path);

void batchmode(ValidUser *users, ValidDriver *drivers, Ride *rides, DriverCity *driverrides, int t_users, int t_drivers, int t_rides, int t_dc ,char* commands);

void iterativemode(ValidUser *users, ValidDriver *drivers, Ride *rides, DriverCity *driverrides, int t_users, int t_drivers, int t_rides, int t_dc);

#endif