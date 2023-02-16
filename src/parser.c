#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/users.h"
#include "../include/parser.h"
#include "../include/query.h"



void get_fields(char *line, char** fields) {
	for(int i = 0 ; line != NULL ; i++) {
		fields[i] = strdup(strsep(&line,";\r\n")); // separates line fields
	}
}

int verifyDate(char *str,char year[],char month[],char day[]) {
	if(onlyDigitsDate(str) == 1) return 1;
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
	if (atoi(day) > 31 || atoi(day) < 1 || atoi(month) > 12 || atoi(month) < 1 ) return 1;

    strcpy(str, year);
    strcat(str, month);
    strcat(str, day);
    return 0;
}

int onlyDigitsDate(char *aux){
  int day, month, year;
  if (strlen(aux) != 10)return 1;
  if (sscanf(aux, "%2d/%2d/%4d", &day, &month, &year) != 3)return 1;
  if ((month < 1 || month > 12) &&  (day < 1 || day > 31))return 1;
  return 0;
}

void toLower(char *str, int n) {
    for (int i = 0; i < n; i++) {
        str[i] = tolower(str[i]);
    }
}

int verifyCarClass(char *class) {
	toLower(class,strlen(class)+1);

	if ((strcmp(class, "basic")==0) || (strcmp(class, "green")==0) || (strcmp(class, "premium")==0)) {
		return 0;
	}
	else return 1;
}

int verifyAccountStatus(char *status) {
	toLower(status,strlen(status)+1);

	if (strcmp(status, "active")==0 || strcmp(status, "inactive")==0) {
		return 0;
	}
	else  return -1;
}

int onlyDigits(char *aux){
  for(int i = 0;i < strlen(aux);i++){
    if(!isdigit(aux[i])) return 1;
  }
  return 0;
}

int verifyInt(char *num) {
	if(onlyDigits(num) == 0 && strlen(num) > 0 && atoi(num) > 0) return 0;
	else return 1; 
}

int onlyDigitsDouble(char *aux){
  for(int i = 0;i < strlen(aux);i++){
    if(!isdigit(aux[i]) && aux[i] != '.') return 1;
  }
  return 0;
}

int verifyIntdecimal(char *aux){
  if(onlyDigitsDouble(aux) == 0 && strlen(aux) > 0 && atof(aux) >= 0)return 0;
  else return 1;
}

void parser_users(Cat_Users cat_users, char* path) {
    char *f_path = "/users.csv";
	char tmp[40];
	strcpy(tmp, path);
	strcat(tmp, f_path);

	FILE *f_users = fopen(tmp, "r");

	if (f_users == NULL) { puts("Missing file in users parser"); return; } 

	char buffer[1000];
	char* fields[7]; 
	char year[5], month[3], day[3];
	
	fgets(buffer, 1000, f_users); 
	
	while (fgets(buffer, 1000, f_users) != NULL) { 
		get_fields(buffer, fields);
		if ((strlen(fields[0]) > 0) && (strlen(fields[1]) > 0) && (strlen(fields[2]) > 0) && (verifyDate(fields[3],year,month,day) == 0) && (verifyDate(fields[4],year,month,day) == 0) && (strlen(fields[5]) > 0) && (verifyAccountStatus(fields[6]) == 0)) {
			insert_user(fields[0], create_user(fields), cat_users); 
		}
        
	}
	printf("Hashtable dos users criada com %d válidos\n",get_cat_users_length(cat_users));

	fclose(f_users);
}

void parser_drivers(Cat_Drivers cat_drivers, char* path) {
    char *f_path = "/drivers.csv";
	char tmp[40];
	strcpy(tmp, path);
	strcat(tmp, f_path);

	FILE *f_drivers = fopen(tmp, "r"); 

	if (f_drivers == NULL) { puts("Missing file in drivers parser"); return; } 

	char buffer[1000];
	char* fields[9]; 
	char year[5], month[3], day[3];

	fgets(buffer, 1000, f_drivers); 

	while (fgets(buffer, 1000, f_drivers) != NULL) { 
		get_fields(buffer, fields);
		if ((strlen(fields[0]) > 0) && (strlen(fields[1]) > 0) && (verifyDate(fields[2],year,month,day) == 0)  && (strlen(fields[3]) > 0) && (verifyCarClass(fields[4]) == 0) && (strlen(fields[5]) > 0) && (strlen(fields[6]) > 0) && (verifyDate(fields[7],year,month,day) == 0) && (verifyAccountStatus(fields[8]) == 0)) {
			insert_driver(fields[0], create_driver(fields), cat_drivers); 
		}
	}
	printf("Hashtable dos drivers criada com %d válidos\n",get_cat_size(cat_drivers));
	
	fclose(f_drivers); 
}

int new_rides(Cat_Users cat_users, Cat_Drivers cat_drivers,Cat_Driver_Ride cdr, char* path){
	char *f_path = "/rides.csv";
	char tmp[40];
	strcpy(tmp, path);
	strcat(tmp, f_path);

	char buffer[1000];
	char* fields[10];
	double custoPorRide;
	char year[5], month[3], day[3];
	int valid = 0;
	Driver d;
	User u;

	FILE *val;
  	val = fopen("./entrada/ridetmp.csv", "w");

	FILE *f_rides = fopen(tmp, "r");
	if (f_rides == NULL) { puts("Missing file in rides parser"); exit(1); } 

	fgets(buffer, 1000, f_rides); 
	while(fgets(buffer, 1000, f_rides) != NULL) {
		get_fields(buffer, fields);
		if(search_user(fields[3],cat_users) && search_driver(fields[2],cat_drivers) && strlen(fields[0]) > 0 && verifyDate(fields[1],year,month,day) == 0 && strlen(fields[2]) > 0 && strlen(fields[3]) > 0 && strlen(fields[4]) > 0 && verifyInt(fields[5]) == 0 && verifyIntdecimal(fields[6]) == 0 && verifyIntdecimal(fields[7]) == 0 && verifyIntdecimal(fields[8]) == 0){
			valid++;
			u = search_user(fields[3],cat_users);
			d = search_driver(fields[2],cat_drivers);
			if(get_driver_accountstatus(d) == 'a' )
				insert_driver_ride(fields[7],create_driver_ride(fields[2],fields[4],get_driver_name(d),cdr),cdr);
			custoPorRide = get_custo(d,atoi(fields[5]));
			insert_userinfo(fields,u,custoPorRide);
			insert_driverinfo(fields,d,custoPorRide);
			if(get_user_accountstatus(u) == 'a' && get_driver_accountstatus(d) == 'a' && get_user_gender(u) == get_driver_gender(d))
				sprintf(buffer,"%d;%d;%s;%f;%d;%f;%c;%s;%s;%d;%d;%s;%s\n",atoi(fields[0]), atoi(fields[1]), fields[4], custoPorRide,atoi(fields[5]),atof(fields[8]),get_user_gender(u), fields[3], fields[2], get_user_creationdate(u),get_driver_creationdate(d),get_user_name(u),get_driver_name(d));
			else sprintf(buffer,"%d;%d;%s;%f;%d;%f;%c;%s;%s;%d;%d;%s;%s\n",atoi(fields[0]), atoi(fields[1]), fields[4], custoPorRide,atoi(fields[5]),atof(fields[8]),'D', fields[3], fields[2], get_user_creationdate(u),get_driver_creationdate(d),get_user_name(u),get_driver_name(d));
			fputs(buffer,val);
		}
		free(fields[0]);
    	free(fields[1]);
        free(fields[2]);
        free(fields[3]);
        free(fields[4]); 
		free(fields[5]);
    	free(fields[6]);
        free(fields[7]);
        free(fields[8]);
    	free(fields[9]);
	}

	fclose(f_rides);
	fclose(val);
	return valid;
}

void batchmode(ValidUser *users, ValidDriver *drivers, Ride *rides, DriverCity *driverrides, int t_users, int t_drivers, int t_rides, int t_dc ,char* commands){
	FILE *fptr = fopen(commands, "r");
    
    if (fptr == NULL) { puts("Missing file in batch mode"); return; }
    
    char s[200], outa[40], str[90], *v, *vs, *out;
    int ncommand = 1, show = 1, cc, last = 0;

	char *aux1, *aux2, *aux3;

    while (fgets(s, 200, fptr) != NULL){
        vs = s;
		printf("Conteúdo da linha do ficheiro de comandos: %s",vs);
		v = strsep(&vs," ");
		//ficheiro de output
		sprintf(outa,"Resultados/command%d_output.txt",ncommand);
		out = outa;
		
		cc = atoi(v);
		if(cc == 1){
			aux1 = strsep(&vs," \n");
			querie1(out, str, users, drivers, t_users, t_drivers, aux1, show, ncommand);
			printf("Query1 executada.\n\n");
		}else if (cc == 2){ 
			aux1 = strsep(&vs," \n");
			querie2(out, str, drivers, t_drivers, atoi(aux1), show, ncommand);
			printf("Query2 executada.\n\n");
		}else if (cc == 3){
			aux1 = strsep(&vs," \n");
			querie3(out, str, users, t_users, atoi(aux1), show, ncommand);
			printf("Query3 executada.\n\n");
		}else if (cc == 4){
			aux1 = strsep(&vs," \n");
			querie4(out, str, rides, t_rides, aux1, show, ncommand);
			printf("Query4 executada.\n\n");
		}else if (cc == 5){
			aux1 = strsep(&vs," \n");
			aux2 = strsep(&vs," \n");
			querie5(out, str, rides, t_rides, aux1, aux2, show, ncommand);
			printf("Query5 executada.\n\n");
		}else if (cc == 6){
			aux1 = strsep(&vs," \n");
			aux2 = strsep(&vs," \n");
			aux3 = strsep(&vs," \n");
			querie6(out, str, rides, t_rides, aux1, aux2, aux3, show, ncommand);
			printf("Query6 executada.\n\n");
		}else if (cc == 7){
			aux1 = strsep(&vs," \n");
			aux2 = strsep(&vs," \n");
			querie7(out, str, driverrides, t_dc , aux2, atoi(aux1), show, ncommand);
			printf("Query7 executada.\n\n");
		}else if (cc == 8){
			aux1 = strsep(&vs," \n");
			aux2 = strsep(&vs," \n");
			querie8(out, str, rides, t_rides, aux1[0], atoi(aux2), show, ncommand, last);
			printf("Query8 executada.\n\n");
		}else if (cc == 9){
			aux1 = strsep(&vs," \n");
			aux2 = strsep(&vs," \n");
			querie9(out, str, rides, t_rides, aux1, aux2, show, ncommand, last);
			printf("Query9 executada.\n\n");
		}else printf("Numero de Query desconhecido!!!!!!!!!!!!!!!!!!!!\n");
    	ncommand++;
    }
    fclose(fptr);
    
}

void iterativemode(ValidUser *users, ValidDriver *drivers, Ride *rides, DriverCity *driverrides, int t_users, int t_drivers, int t_rides, int t_dc ){
	int ncommand = 0, show = 1, last = 0;
	char str[200], outa[40], *out;
	char n[2];
	char buffer[20], buffer2[20], buffer3[20];

	while(true){

		sprintf(outa,"Resultados/command%d_output.txt",ncommand);
		out = outa;

		printf("digite o numero de Querry que pretende?\n");
		scanf("%s",n);
		int num = atoi(n);
		if(num == 1){
			printf("digite um id a precorar\n");
			scanf("%s",buffer);
			querie1(out, str, users, drivers, t_users, t_drivers, buffer, show, ncommand);
			printf("Query1 executada.\n\n");
		}else if (num == 2){ 
			printf("Digita o limite do top avaliaçoes medias para os drivers que pretende\n");
			scanf("%s",buffer);
        	querie2(out, str, drivers,t_drivers, atoi(buffer), show, ncommand);
			printf("Query2 executada.\n\n");
    	}else if (num == 3){
			printf("Digita o limite do top distancias percorridas por users que pretende\n");
			scanf("%s",buffer);
        	querie3(out, str, users, t_users, atoi(buffer), show, ncommand);
			printf("Query3 executada.\n\n");
    		}else if (num == 4){
			printf("digite o nome da cidade da qual pretende saber a media de preço\n");
			scanf("%s",buffer);
			querie4(out, str, rides, t_rides, buffer, show, ncommand);
			printf("Query4 executada.\n\n");
		}else if (num == 5){
			printf("digite a data de limite inferior da procura(no formato dd/mm/aaaa)\n");
			scanf("%s",buffer);
			printf("digite a data de limite superior da procura(no formato dd/mm/aaaa)\n");
			scanf("%s",buffer2);
        	querie5(out, str, rides, t_rides, buffer, buffer2, show, ncommand);
			printf("Query5 executada.\n\n");
		}else if (num == 6){
			printf("digite o nome da cidade da qual pretende saber a media de preço\n");
			scanf("%s",buffer);
			printf("digite a data de limite inferior da procura(no formato dd/mm/aaaa)\n");
			scanf("%s",buffer2);
			printf("digite a data de limite superior da procura(no formato dd/mm/aaaa)\n");
			scanf("%s",buffer3);
        	querie6(out, str, rides, t_rides, buffer, buffer2, buffer3, show, ncommand);
			printf("Query6 executada.\n\n");
		}else if (num == 7){
			printf("digite o número condutores do qual pretende saber o top \n");
			scanf("%s",buffer2);
			printf("digite o nome da cidade da qual pretende saber a media de preço\n");
			scanf("%s",buffer);
        	querie7(out, str, driverrides, t_dc , buffer, atoi(buffer2), show, ncommand);
			printf("Query7 executada.\n\n");
		}else if (num == 8){
			printf("digite o genero do qual pretende passar como parametro\n");
			scanf("%s",buffer);
			printf("digite a idade do qual pretende passar como parametro)\n");
			scanf("%s",buffer2);
        	querie8(out, str, rides, t_rides, buffer[0], atoi(buffer2), show, ncommand, last);
			printf("Query8 executada.\n\n");
		}else if (num == 9){
			printf("digite a data de limite inferior da procura(no formato dd/mm/aaaa)\n");
			scanf("%s",buffer);
			printf("digite a data de limite superior da procura(no formato dd/mm/aaaa)\n");
			scanf("%s",buffer2);
        	querie9(out, str, rides, t_rides, buffer, buffer2, show, ncommand, last);
			printf("Query9 executada.\n\n");
		}else printf("Numero de Query desconhecido!!!!!!!!!!!!!!!!!!!!\n");
		ncommand++;
	}
}