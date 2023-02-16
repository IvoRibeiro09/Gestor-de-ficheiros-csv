#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include "../include/validDriver.h"
#include "../include/queryaux.h"
#include "../include/parser.h"
#include <stdbool.h>

struct validdriver {
	int id;
	char *name;
	int age;
	char gender;
    double avmedia;
    double totalganho;
    short int nviagens;
	int lastride;
};

ValidDriver create_validdriver(char **fields){
	ValidDriver d = malloc(sizeof(struct validdriver));

	d->id = atoi(fields[0]);
	d->name = strdup(fields[1]);
	d->gender = fields[2][0];
	d->age = atoi(fields[3]);
	d->avmedia = atof(fields[4]);
	d->totalganho = atof(fields[5]);
	d->nviagens = atoi(fields[6]);
	d->lastride = atoi(fields[7]);

	return d;
}

//getters
int get_validDriver_id(ValidDriver data) {
	return data->id;
}

char *get_validDriver_name(ValidDriver data) {
	return data->name;
}

int get_validDriver_age(ValidDriver data) {
    return data->age;
}

char get_validDriver_gender(ValidDriver data) {
    return data->gender;
}

double get_validDriver_avmedia(ValidDriver data){
	return data->avmedia;
}

double get_validDriver_totalganho(ValidDriver data){
	return data->totalganho;
}

int get_validDriver_nviagens(ValidDriver data){
	return data->nviagens;
}

int get_validDriver_lastride(ValidDriver data){
	return data->lastride;
}

//função que cria um array de condutores a partir do ficheiro auxiliar que criamos
ValidDriver *get_drivers_list(int tamanho){

	ValidDriver *drivers = malloc(sizeof(struct validdriver) * (tamanho));

	FILE *fdriver = fopen("entrada/drivertmp.csv","r");
	if (fdriver == NULL) { puts("Missing file userstmp"); exit(1); } 

	char buffer[2000];
	char* fields[8]; 
	int j = 0;

	while (fgets(buffer, 2000, fdriver) != NULL) { 
		get_fields(buffer, fields);
		drivers[j] = create_validdriver(fields);
		j++;
		free(fields[0]);
        free(fields[1]);
    	free(fields[2]);
		free(fields[3]);
        free(fields[4]);
    	free(fields[5]);
		free(fields[6]);
        free(fields[7]);
	}

	ordenaDrivers(drivers,0,j-1);
	printf("Lista de Drivers ativos criada com %d válidos\n",j);

	return drivers;
}

//funçoes de ordenaçao la lista de drivers validos
void ordenaDrivers(ValidDriver *arr,int l, int r){
	if (l < r) {
        int m = l + (r - l) / 2;
        ordenaDrivers(arr, l, m);
        ordenaDrivers(arr, m + 1, r);
        mergeaux2(arr, l, m, r);
    }
}

void mergeaux2(ValidDriver *arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    ValidDriver L[n1], R[n2];
 
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
		if(L[i]->avmedia/L[i]->nviagens == R[j]->avmedia/R[j]->nviagens){
			if(L[i]->lastride == R[j]->lastride){
				if(L[i]->id < R[j]->id){
					arr[k] = L[i];
        			i++;
				}else{
					arr[k]= R[j];
					j++;
				}
			}else if(L[i]->lastride > R[j]->lastride){
				arr[k] = L[i];
        		i++;
			}else{
				arr[k]= R[j];
				j++;
			}
		}else if(L[i]->avmedia/L[i]->nviagens > R[j]->avmedia/R[j]->nviagens){
			arr[k] = L[i];
        	i++;
		}else{
            arr[k] = R[j];
        	j++;
    	}
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//função que indica se o condutor com id passado existe
bool isDriver(ValidDriver *drivers, int t_d, char *username,char str[],int show){
	for(int i=0; i < t_d ;i++){
        if(atoi(username) == drivers[i]->id){
            sprintf(str,"%s;%c;%d;%.3f;%d;%.3f\n", drivers[i]->name, drivers[i]->gender, get_age(drivers[i]->age), drivers[i]->avmedia/drivers[i]->nviagens, drivers[i]->nviagens, drivers[i]->totalganho);
            if(show == 1)printf("Driver encontrado: %s",str);
			return true;
        }
    }
	return false;
}

//função responsavel por libertar a memoria allocada com o array destas estruturas 
void free_arraydrivers(ValidDriver *arr, int t){
	for (int i=0; i < t; i++) {
	   free(arr[i]->name);
	   free(arr[i]);
	}
	free(arr);
}