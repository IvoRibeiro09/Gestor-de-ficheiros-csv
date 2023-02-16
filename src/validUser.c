#include <stdio.h>
#include <glib.h>
#include "../include/users.h"
#include "../include/queryaux.h"
#include "../include/parser.h"
#include <stdbool.h>

//nova estrutura de dados usada nas queries apenas com informação util
struct validuser {
    char *id;
    char *name; 
    char gender;  
    int age;
	short int totaldistance;
    double avmedia;
    double totalgasto;
    short int nviagens;
	int lastride;
};

ValidUser create_validuser(char **fields){
	ValidUser user = malloc(sizeof(struct validuser));

	user->id = strdup(fields[0]);
	user->name = strdup(fields[1]);
	user->gender = fields[2][0];
	user->age = atoi(fields[3]);
	user->totaldistance = atoi(fields[4]);
	user->avmedia = atof(fields[5]);
	user->totalgasto = atof(fields[6]);
	user->nviagens = atoi(fields[7]);
	user->lastride = atoi(fields[8]);

	return user;
}

//geters
char* get_validUser_id(ValidUser data) { 
	return data->id;
}

char *get_validUser_name(ValidUser data) {
	return data->name;
}

char get_validUser_gender(ValidUser data) {
    return data->gender;
}

int get_validUser_age(ValidUser data) {
    return data->age;
}

int get_validUser_totaldistance(ValidUser data){
	return data->totaldistance;
}

double get_validUser_avmedia(ValidUser data){
	return data->avmedia;
}

double get_validUser_totalgasto(ValidUser data){
	return data->totalgasto;
}

int get_validUser_nviagens(ValidUser data){
	return data->nviagens;
}

int get_validUser_lastride(ValidUser data){
	return data->lastride;
}

//função que cria a lista de users ativos com base no ficheiro auxiliar criado por nós
ValidUser *get_users_list(int tamanho){

	ValidUser *users = malloc(sizeof(struct validuser) * (tamanho));

	FILE *fusers = fopen("entrada/usertmp.csv","r");
	if (fusers == NULL) { puts("Missing file userstmp"); exit(1); } 

	char buffer[2000];
	char* fields[9]; 
	int j = 0;

	while (fgets(buffer, 2000, fusers) != NULL) { 
		get_fields(buffer, fields);
		users[j] = create_validuser(fields);
		j++;
		free(fields[0]);
        free(fields[1]);
    	free(fields[2]);
		free(fields[3]);
        free(fields[4]);
    	free(fields[5]);
		free(fields[6]);
		free(fields[7]);
        free(fields[8]);
	}

	ordenaUsers(users,0,j-1);
	printf("Lista de Users ativos criada com %d válidos\n",j);

	fclose(fusers);

	return users;
}

//funçoes de ordenaçao dos users
void ordenaUsers(ValidUser arr[],int l, int r){
	if (l < r) {
        int m = l + (r - l) / 2;
        ordenaUsers(arr, l, m);
        ordenaUsers(arr, m + 1, r);
        mergeaux3(arr, l, m, r);
    }
}

void mergeaux3(ValidUser arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    ValidUser L[n1], R[n2];
 
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
		if(L[i]->totaldistance == R[j]->totaldistance){
			if(L[i]->lastride == R[j]->lastride){
				if(strcmp(L[i]->id,R[j]->id) < 0){
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
		}else if(L[i]->totaldistance > R[j]->totaldistance){
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

//função que indica se o utilizar com id passado existe
bool isUser(ValidUser *users, int t_u, char *username,char str[],int show){
	for(int i=0; i < t_u ;i++){
        if(strcmp(username,users[i]->id) == 0){
            sprintf(str,"%s;%c;%d;%.3f;%d;%.3f\n",users[i]->name, users[i]->gender,get_age(users[i]->age), users[i]->avmedia/users[i]->nviagens, users[i]->nviagens, users[i]->totalgasto);
            if(show == 1)printf("User encontrado: %s",str); 
            return true;
        }
    }
	return false;
}

//função responsavel por libertar a memoria allocada com o array destas estruturas 
void free_arrayuser(ValidUser *arr ,int t){
	for (int i=0; i < t ; i++) {
 	   free(arr[i]->id);
	   free(arr[i]->name);
	   free(arr[i]);
	}
	free(arr);
}