#ifndef DRIVERS_
#define DRIVERS_
#include <stdbool.h>
#include <glib.h>


typedef struct cat_drivers *Cat_Drivers;
typedef struct driver *Driver;

Driver create_driver(char **fields);

Cat_Drivers create_driver_cat();

Cat_Drivers insert_driver(char *key, Driver data, Cat_Drivers cat_drivers);

void insert_driverinfo(char **fields,Driver driver, double custoPorRide);

Driver search_driver(char *key, Cat_Drivers cat_drivers);

Driver search_driver_int(int id, Cat_Drivers cat_drivers);

int get_cat_size(Cat_Drivers cat_drivers);
//geters
char *get_driver_id(Driver data);

char *get_driver_name(Driver data);

int get_driver_age(Driver data);

char get_driver_gender(Driver data);

char get_driver_carclass(Driver data);

int get_driver_creationdate(Driver data);

char get_driver_accountstatus(Driver data);

double get_driver_avmedia(Driver data);

double get_driver_totalganho(Driver data);

int get_driver_nviagens(Driver data);

int get_driver_lastride(Driver data);

double get_custo(Driver data, int distance);

int new_driver(Cat_Drivers cat_drivers);

void free_cat_drivers(Cat_Drivers cat_drivers);

void free_cat_drivers_func(gpointer key, gpointer value, gpointer data);

#endif