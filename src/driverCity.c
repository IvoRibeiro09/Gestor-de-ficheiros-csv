#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include "../include/driverCity.h"
#include "../include/queryaux.h"
#include "../include/parser.h"

//nova estrutura que identifica os conjuntos condutor cidade da viagem
struct drivercity{
    int id;
    char *city;
    char *nome;  
	double score;
    int n;
};

DriverCity drivercity_create(char **fields){

    DriverCity dc = malloc(sizeof(struct drivercity));

    dc->id = atoi(fields[0]);
    dc->city = strdup(fields[1]);
    dc->nome = strdup(fields[2]);
    dc->score = atof(fields[3]);
    dc->n = atoi(fields[4]);

    return dc;
}

int get_drivercity_id(DriverCity data){
    return data->id;
}

char *get_drivercity_city(DriverCity data){
    return data->city;
}

char *get_drivercity_name(DriverCity data){
    return data->nome;
}

double get_drivercity_score(DriverCity data){
    return data->score;
}

int get_drivercity_n(DriverCity data){
    return data->n;
}

//função que cria a lista de conjuntos condutor/cidade que foi anteriormente aramazenda num ficheiro auxiliar
DriverCity *get_drivercity_list(int tamanho){

    DriverCity *auxdc = malloc(sizeof(struct drivercity) * (tamanho));

    FILE *fdc = fopen("entrada/driverridetmp.csv","r");
    if (fdc == NULL) { puts("Missing file driverridetmp"); exit(1); } 

    char buffer[2000];
	char* fields[5]; 
	int j = 0;

	while (fgets(buffer, 2000, fdc) != NULL) { 
		get_fields(buffer, fields);
		auxdc[j] = drivercity_create(fields);
		j++;
        free(fields[0]);
        free(fields[1]);
    	free(fields[2]);
        free(fields[3]);
        free(fields[4]);
	}

    ordenaDriverRides(auxdc,0,j-1);

    fclose(fdc);

    return auxdc;
}

//conjunto de duas funções responsaveis por ordenar o array de conjuntos condutor/cidade
void ordenaDriverRides(DriverCity arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        ordenaDriverRides(arr, l, m);
        ordenaDriverRides(arr, m + 1, r);
        mergeaux7(arr, l, m, r);
    }
}

void mergeaux7(DriverCity arr[],int l,int m,int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    DriverCity L[n1], R[n2];
 
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
		if(L[i]->score/L[i]->n == R[j]->score/R[j]->n){
            if(L[i]->id > R[j]->id){
                arr[k] = L[i];
                i++;
            }else{
                arr[k] = R[j];
                j++;
            }
		}else if (L[i]->score/L[i]->n > R[j]->score/R[j]->n) {
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

//função responsavel por libertar a memoria allocada com o array destas estruturas 
void free_arraydr(DriverCity *arr, int t){
    for (int i=0; i < t ; i++) {
       free(arr[i]->city);
       free(arr[i]->nome);
       free(arr[i]);
    }
    free(arr);
}