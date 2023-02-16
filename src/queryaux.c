#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/query.h"
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#define dia 9
#define mes 10
#define ano 2022

//funções auxiliares 

//converter uma data dd/mm/aaaa em int ddmmaaaa 
int dateInt(char* str){
	char year[5], month[3], day[3];
	for (int i = 0; i < 4; i++) {
        year[i] = str[i + 6];
    }
    year[4] = '\0';
    for (int i = 0; i < 2; i++) {
        month[i] = str[i + 3];
		day[i] = str[i];
    }
    month[2] = '\0';
    day[2] = '\0';

	return atoi(year)*10000 +atoi(month)*100 +atoi(day);
}

//converte uma data em inteiro ddmmaaaa para um inteiro que indica a idade
int get_age(int age){
    int res = ano - age/10000;
    if(mes == (age/100)%100) {
        if(dia < age%100) res --;
    }else if(mes < (age/100)%100) res --;
    return res;
}

//converte um inteiro de id aaaa para uma string 0000000aaaa
char *get_fullid(int id){
    char n[12];
    sprintf(n,"%d",id);
    char fullid[12] = "000000000000";
    for (int i = strlen(n);i >0;i--){
        fullid[12-i] = n[strlen(n)-i];
    }
    return strdup(fullid);
}

//converte uma data em inteiro ddmmaaaa numa string dd/mm/aaaa
char* dateChar(int age){
	char n[11];
	sprintf(n,"%02d/%02d/%d",age%100,(age/100)%100,age/10000);
	return strdup(n);
}

//concatena a string do id do driver com a da cidade de uma ride 
//para facilitar a execução da query 7
char *my_concat(char *s1,char *s2){
	char buffer[30];

	strcpy(buffer,s1);
	strcat(buffer," ");
	strcat(buffer,s2);

    return strdup(buffer);
}