#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include "../include/driver_ride.h"
#include "../include/queryaux.h"
#include "../include/parser.h"

//estrutura usada para identificar todas as viagens
// de um determinado condutor numa determinada cidade

struct driver_ride{
    char *id_city;
    char *nome;
	double score;
    int n;
};

struct cat_driver_ride{
	GHashTable* driver_ride;
};

Driver_Ride create_driver_ride(char* driverId, char* city,char* nome, Cat_Driver_Ride cdr){
    char* id = my_concat(driverId,city);
    if(search_driver_ride(id,cdr)){
    Driver_Ride dr = search_driver_ride(id,cdr);
    free(id);
    return dr;
    }
    else{
        Driver_Ride dr = malloc(sizeof(struct driver_ride));

        dr->id_city = strdup(id);
        dr->nome = nome;
        dr->score = 0;
        dr->n = 0;

        free(id);
        return dr;
    }
}

Cat_Driver_Ride create_driver_ride_cat(){
    Cat_Driver_Ride cdr = malloc(sizeof(struct cat_driver_ride));
    cdr->driver_ride = g_hash_table_new(g_str_hash, g_str_equal);
    return cdr;
}

Cat_Driver_Ride insert_driver_ride(char *score,Driver_Ride dr ,Cat_Driver_Ride cdr) {
    dr->score += atof(score);
    dr->n++;
    g_hash_table_insert(cdr->driver_ride,dr->id_city, dr);
    return cdr;
}

int getsize(Cat_Driver_Ride cdr){
    return g_hash_table_size(cdr->driver_ride);
}

Driver_Ride search_driver_ride(char *key, Cat_Driver_Ride cdr) {
	return (g_hash_table_lookup(cdr->driver_ride, key));
}

char *get_driver_ride_id_city(Driver_Ride data){
    return strdup(data->id_city);
}

char *get_driver_ride_name(Driver_Ride data){
    return strdup(data->nome);
}

double get_driver_ride_score(Driver_Ride data){
    return data->score;
}

int get_driver_ride_n(Driver_Ride data){
    return data->n;
}

//função que escreve num novo ficheiro toda a informaçao antes inserida na hashtable
//para que esta possa ser destruida e toda a memoria por ela usada ser libertada
int new_driverride(Cat_Driver_Ride cdr){

    GList *aux = g_hash_table_get_values(cdr->driver_ride);
    int i=0;
    char buffer[2000];

    FILE *val;
  	val = fopen("./entrada/driverridetmp.csv", "w");

    Driver_Ride d;
    char *id_city;
    char *valor;

    while(aux != NULL){
        i++;
        d = aux->data;
        id_city = d->id_city;
        valor = strsep(&id_city," \t");
        sprintf(buffer,"%d;%s;%s;%f;%d\n",atoi(valor), id_city, d->nome,d->score,d->n);
		fputs(buffer,val);
        aux = aux->next;
    }

    g_list_free(aux);

    fclose(val);

    return i;
}

//conjunto de duas funções responsaveis por destruir e libertar toda a memoria utilizada na hashtable 
void free_cat_driver_ride(Cat_Driver_Ride cdr){
    g_hash_table_foreach(cdr->driver_ride, free_cat_dr_func, NULL);
    g_hash_table_destroy(cdr->driver_ride);
    free(cdr);
}

void free_cat_dr_func(gpointer key, gpointer value, gpointer data){
    Driver_Ride dr = (Driver_Ride) value;
    free(key);
}