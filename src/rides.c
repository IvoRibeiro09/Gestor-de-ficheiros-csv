#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/parser.h"

// rides struct
struct ride {
	int id;
	int date;
	char *city; 
	double custo;
	short int distance;
	double tip;
	char genero; //M dois M , F dosi F , D de diferentes
	int idDriver;
	char *idUser;
	int accAgeUser; 
	int accAgeDriver; 
	char *username;
	char *drivername; 
};

//geters
int get_ride_id(Ride data) {
    return data->id;
}

int get_ride_date(Ride data){
	return (data->date);
}

char *get_ride_city(Ride data) {
	return data->city;
}

double get_ride_custo(Ride data) {
	return data->custo;
}

int get_ride_distance(Ride data){
	return data->distance;
}

double get_ride_tip(Ride data){
	return data->tip;
}

char get_ride_genero(Ride data){
	return data->genero;
}

int get_ride_idDriver(Ride data){
	return data->idDriver;
}

char *get_ride_idUser(Ride data){
	return data->idUser;
}

int get_ride_accAgeUser(Ride data){
	return data->accAgeUser;
}

int get_ride_accAgeDriver(Ride data){
	return data->accAgeDriver;
}

char *get_ride_username(Ride data){
	return data->username;
}

char *get_ride_drivername(Ride data){
	return data->drivername;
}

// função auxiliar para a leitura do ficheiro auxiliar
Ride create_validride(char **fields){
	Ride ride = malloc(sizeof(struct ride));

	ride->id = atoi(fields[0]);
	ride->date = atoi(fields[1]);
	ride->city = fields[2];
	ride->custo = atof(fields[3]);
	ride->distance = atoi(fields[4]);
	ride->tip = atof(fields[5]);
	ride->genero = fields[6][0];
	ride->idUser = fields[7];
	ride->idDriver = atoi(fields[8]);
	ride->accAgeUser = atoi(fields[9]);
	ride->accAgeDriver = atoi(fields[10]);
	ride->username = fields[11];
	ride->drivername = fields[12];

	return ride;
}

// função que cria o array de viagens a partir da informaçao do novo ficheiro 
Ride *get_rides_list(int tamanho){

	Ride *rides = malloc(sizeof(struct ride) * (tamanho));

	FILE *frides = fopen("entrada/ridetmp.csv","r");
	if (frides == NULL) { puts("Missing file ridetmp"); exit(1); } 

	char buffer[2000];
	char* fields[13]; 
	int j = 0;

	while (fgets(buffer, 2000, frides) != NULL) { 
		get_fields(buffer, fields);
		rides[j] = create_validride(fields);
		j++;
		free(fields[0]);
    	free(fields[1]);
        free(fields[3]);
        free(fields[4]); 
		free(fields[5]);
    	free(fields[6]);
        free(fields[8]);
    	free(fields[9]);
		free(fields[10]);
	}

	printf("Lista de Rides criada com %d válidos\n",j);
	return rides;
}

//funçoes de ordenação de todos os rides para os requisitos pedidos na query 9
void ordenaRides(Ride *arr, int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        ordenaRides(arr, l, m);
        ordenaRides(arr, m + 1, r);
        mergeaux9(arr, l, m, r);
    }
}

void mergeaux9(Ride *arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
	Ride *L = malloc(sizeof(struct ride) * (n1)), *R = malloc(sizeof(struct ride) * (n2));
 
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
		if(L[i]->distance == R[j]->distance){
			if(L[i]->date == R[j]->date){
				if(L[i]->id > R[j]->id){
					arr[k] = L[i];
            		i++;
				}else{
					arr[k] = R[j];
					j++;
				}
			}else if(L[i]->date > R[j]->date){
				arr[k] = L[i];
            	i++;
			}else{
				arr[k]= R[j];
				j++;
			}
		}else if(L[i]->distance > R[j]->distance){
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
	free(L);
	free(R);
}

//funçoes de ordenação de todos os rides para os requisitos pedidos na query 8
void ordenaValidos(Ride arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        ordenaValidos(arr, l, m);
        ordenaValidos(arr, m + 1, r);
        mergeaux8(arr, l, m, r);
    }
}

void mergeaux8(Ride arr[], int l, int m, int r){
 	int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
	Ride *L = malloc(sizeof(struct ride) * (n1)), *R = malloc(sizeof(struct ride) * (n2));
    
	for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
		if(L[i]->accAgeDriver == R[j]->accAgeDriver){
			if(L[i]->accAgeUser == R[j]->accAgeUser){
				if(L[i]->id < R[j]->id){
					arr[k] = L[i];
            		i++;
				}else{
					arr[k] = R[j];
					j++;
				}
			}else if(L[i]->accAgeUser < R[j]->accAgeUser){
				arr[k] = L[i];
            	i++;
			}else{
				arr[k]= R[j];
				j++;
			}
		}else if(L[i]->accAgeDriver < R[j]->accAgeDriver){
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
	free(L);
	free(R);
}



//função responsavel por libertar a memoria allocada com o array destas estruturas 
void free_arrayrides(Ride *arr, int t){
	for (int i=0; i < t ; i++) {
	   free(arr[i]->city);
	   free(arr[i]->idUser);
	   free(arr[i]->drivername);
	   free(arr[i]->username);
	   free(arr[i]);
	}
	free(arr);
}