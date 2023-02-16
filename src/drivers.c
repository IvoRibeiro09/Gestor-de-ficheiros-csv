#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include "../include/drivers.h"
#include "../include/queryaux.h"
#include "../include/parser.h"
#include <stdbool.h>

// drivers struct
struct driver {
	char *id;
	char *name;
	int age;
	char gender;
	char car_class; 
	int creationdate; 
	char account_status; 
	//rides
    double avmedia;
    double totalganho;
    short int nviagens;
	int lastride;
};

// drivers catalogue
struct cat_drivers {
	GHashTable* drivers; // hashtable for drivers
};

// creates a driver object
Driver create_driver(char **fields) {

	Driver driver = malloc(sizeof(struct driver));
	
	driver->id = fields[0];
	driver->name = fields[1];
	driver->age = atoi(fields[2]);
	driver->gender = fields[3][0];
	driver->car_class = fields[4][0];
	driver->creationdate = atoi(fields[7]);
	driver->account_status = fields[8][0];
	driver->avmedia = 0;
	driver->totalganho = 0;
	driver->nviagens = 0;
	driver->lastride = 0;

	return driver;
}

Cat_Drivers create_driver_cat() {
	Cat_Drivers cat_drivers = malloc(sizeof(struct cat_drivers));
	cat_drivers->drivers = g_hash_table_new(g_str_hash, g_str_equal);
	return cat_drivers;
}

Cat_Drivers insert_driver(char *key, Driver data, Cat_Drivers cat_drivers) {
	g_hash_table_insert(cat_drivers->drivers, key, data);
	return cat_drivers;
}

void insert_driverinfo(char **fields,Driver driver, double custoPorRide){
	
	driver->avmedia += atof(fields[7]);
	driver->totalganho += atof(fields[8]) + custoPorRide;
	driver->nviagens ++;
	if(atoi(fields[1]) > driver->lastride){
		driver->lastride = atoi(fields[1]);
	}
}

Driver search_driver(char *key, Cat_Drivers cat_drivers) {
	return (g_hash_table_lookup(cat_drivers->drivers, key));
}

Driver search_driver_int(int id, Cat_Drivers cat_drivers) {
	return (g_hash_table_lookup(cat_drivers->drivers, get_fullid(id)));
}

int get_cat_size(Cat_Drivers cat_drivers){
	return g_hash_table_size(cat_drivers->drivers);
}

//getters
char *get_driver_id(Driver data) {
	return data->id;
}

char *get_driver_name(Driver data) {
	return data->name;
}

int get_driver_age(Driver data) {
    return data->age;
}

char get_driver_gender(Driver data) {
    return data->gender;
}

char get_driver_carclass(Driver data) {
    return data->car_class;
}

int get_driver_creationdate(Driver data) {
    return data->creationdate;
}

char get_driver_accountstatus(Driver data) {
    return data->account_status;
}

double get_driver_avmedia(Driver data){
	return data->avmedia;
}

double get_driver_totalganho(Driver data){
	return data->totalganho;
}

int get_driver_nviagens(Driver data){
	return data->nviagens;
}

int get_driver_lastride(Driver data){
	return data->lastride;
}

double get_custo(Driver data, int distance){
	if (data->car_class == 'b') {
		return (3.25 + 0.62*(distance));
	}
	else if (data->car_class == 'g'){
		return  (4 + 0.79*(distance));
	}else if (data->car_class == 'p'){
		return (5.20 + 0.94*(distance));
	}else return 0;
}

//função que escreve num ficheiro auxiliar informaçao util sobre os condutores
int new_driver(Cat_Drivers cat_drivers){
	
	GList *aux = g_hash_table_get_values(cat_drivers->drivers);
	int i=0;
	char buffer[2000];

	FILE *val;
  	val = fopen("./entrada/drivertmp.csv", "w");

	Driver d;
    
    while(aux != NULL){
        d = aux->data;
		if(d->account_status == 'a'){
			sprintf(buffer,"%d;%s;%c;%d;%f;%f;%d;%d\n",atoi(d->id), d->name,d->gender, d->age,d->avmedia,d->totalganho,d->nviagens,d->lastride);
			fputs(buffer,val);
			i++;
		}
        aux = aux->next;
    }

    g_list_free(aux);
	fclose(val);

    return i;
}

//conjunto de duas funções responsaveis por destruir e libertar toda a memoria utilizada na hashtable 
void free_cat_drivers(Cat_Drivers cat_drivers){
	g_hash_table_foreach(cat_drivers->drivers,free_cat_drivers_func,NULL);
    g_hash_table_destroy(cat_drivers->drivers);
    free(cat_drivers);
}

void free_cat_drivers_func(gpointer key, gpointer value, gpointer data){
    Driver driver = (Driver) value;
    free(driver->name);
    free(key);
}

