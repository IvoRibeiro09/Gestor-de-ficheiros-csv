#include <stdio.h>
#include <glib.h>
#include "../include/users.h"
#include "../include/queryaux.h"
#include "../include/parser.h"
#include <stdbool.h>

// users struct
struct user {
    char *id;
    char *name; 
    char gender;  
    int age; // dd/mm/aaaa 
	int creationdate;
    char account_status; // active ou inactive 
	//rides
	short int totaldistance;
    double avmedia;
    double totalgasto;
    short int nviagens;
	int lastride;
}; 


struct cat_users { 
	GHashTable* users; 
};

// create a user object
User create_user(char **fields) {
	User user = malloc(sizeof(struct user));

	user->id = fields[0];
	user->name = fields[1];
	user->gender = fields[2][0];
	user->age= atoi(fields[3]);
	user->creationdate = atoi(fields[4]);
	user->account_status = fields[6][0];
	user->totaldistance = 0;
	user->avmedia = 0;
	user->totalgasto = 0;
	user->nviagens = 0;
	user->lastride = 0;

	return user;
}

// create a users catalog object
Cat_Users create_user_cat() {
	Cat_Users cat_users = malloc(sizeof(struct cat_users));
	cat_users->users = g_hash_table_new(g_str_hash, g_str_equal);

	return cat_users;
}

Cat_Users insert_user(char *key, User data, Cat_Users cat_users) {
	g_hash_table_insert(cat_users->users, key, data);
	return cat_users;
}

void insert_userinfo(char **fields,User user,double custoPorRide){
	
	user->totaldistance += atoi(fields[5]);
	user->avmedia += atof(fields[6]);
	user->totalgasto += atof(fields[8]) + custoPorRide;
	user->nviagens ++;
	if(atoi(fields[1]) > user->lastride){
		user->lastride = atoi(fields[1]);
	}
}

User search_user(char *key, Cat_Users cat_users) {
	return (g_hash_table_lookup(cat_users->users, key));
}

int get_cat_users_length(Cat_Users cat_users) {
	return g_hash_table_size(cat_users->users);
}

//geters
char* get_user_id(User data) { 
	return data->id;
}

char *get_user_name(User data) {
	return data->name;
}

char get_user_gender(User data) {
    return data->gender;
}

int get_user_age(User data) {
    return data->age;
}

char get_user_accountstatus(User data) {
    return data->account_status;
}

int get_user_creationdate(User data){
	return data->creationdate;
}

int get_user_totaldistance(User data){
	return data->totaldistance;
}

double get_user_avmedia(User data){
	return data->avmedia;
}

double get_user_totalgasto(User data){
	return data->totalgasto;
}

int get_user_nviagens(User data){
	return data->nviagens;
}

int get_user_lastride(User data){
	return data->lastride;
}

//função que cria o ficheiro auxiliar apenas com informaçao e utilizadores validos e ativos 
int new_user(Cat_Users cat_users){
	
	GList *aux = g_hash_table_get_values(cat_users->users);
	int i=0;
	char buffer[2000];

	FILE *val;
  	val = fopen("./entrada/usertmp.csv", "w");

	User u;
    
    while(aux != NULL){
        u = aux->data;
		if(u->account_status =='a'){
			sprintf(buffer,"%s;%s;%c;%d;%d;%.3f;%.3f;%d;%d\n",u->id, u->name, u->gender,u->age,u->totaldistance,u->avmedia,u->totalgasto,u->nviagens,u->lastride);
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
void free_cat_users_func(gpointer key, gpointer value, gpointer data){
    User user = (User) value;
    free(user->name);
    free(key);
}

void free_cat_users(Cat_Users cat_users){
    g_hash_table_foreach(cat_users->users, free_cat_users_func, NULL);
    g_hash_table_destroy(cat_users->users);
    free(cat_users);
}