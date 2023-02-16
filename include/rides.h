#ifndef RIDES_
#define RIDES_
#include <glib.h>
#include "queryaux.h"

typedef struct ride *Ride;

int get_ride_id(Ride data);

int get_ride_date(Ride data);

char *get_ride_city(Ride data) ;

double get_ride_custo(Ride data) ;

int get_ride_distance(Ride data);

double get_ride_tip(Ride data);

char get_ride_genero(Ride data);

int get_ride_idDriver(Ride data);

char *get_ride_idUser(Ride data);

int get_ride_accAgeUser(Ride data);

int get_ride_accAgeDriver(Ride data);

char *get_ride_username(Ride data);

char *get_ride_drivername(Ride data);

Ride create_validride(char **fields);

Ride *get_rides_list(int tamanho);

//queries
void ordenaRides(Ride arr[], int l, int r);

void mergeaux9(Ride arr[], int l, int m, int r);

void ordenaValidos(Ride arr[], int l, int r);

void mergeaux8(Ride arr[], int l, int m, int r);

void free_arrayrides(Ride *arr , int t);

#endif
