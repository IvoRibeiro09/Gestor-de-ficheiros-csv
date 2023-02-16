#ifndef DRIVERRIDES_
#define DRIVERRIDES_
#include <glib.h>
#include "queryaux.h"

typedef struct cat_driver_ride *Cat_Driver_Ride;
typedef struct driver_ride *Driver_Ride;

Driver_Ride create_driver_ride(char* driverId, char* city,char* nome, Cat_Driver_Ride cdr);

Cat_Driver_Ride create_driver_ride_cat();

Cat_Driver_Ride insert_driver_ride(char *score,Driver_Ride dr, Cat_Driver_Ride cdr);

int getsize(Cat_Driver_Ride cdr);

Driver_Ride search_driver_ride(char *key, Cat_Driver_Ride cdr);

char *get_driver_ride_id_city(Driver_Ride data);

char *get_driver_ride_name(Driver_Ride data);

double get_driver_ride_score(Driver_Ride data);

int get_driver_ride_n(Driver_Ride data);

int new_driverride(Cat_Driver_Ride cdr);

void free_cat_dr_func(gpointer key, gpointer value, gpointer data);

void free_cat_driver_ride(Cat_Driver_Ride cdr);

#endif
