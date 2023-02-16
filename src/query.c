#include "../include/rides.h"
#include "../include/driverCity.h"
#include "../include/validDriver.h"
#include "../include/validUser.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*//////////////////////////
Querie 1
Listar o resumo de um perfil registado no serviço através do seu identificador
/////////////////////////*/
void querie1(char *out, char str[], ValidUser *users, ValidDriver *drivers, int t_u, int t_d, char *username,int show,int ncommand){
	printf("A executar a Query1...\n");
    FILE *ficheiro = fopen(out, "w");
    
    if(isUser(users, t_u, username, str, show)){
        fputs(str,ficheiro);
    }else if(isDriver(drivers, t_d, username, str, show)){
        fputs(str,ficheiro);
    }else if(show == 1)printf("Não existe nenhum User ou Driver com esse id\n");
    
    fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

/*//////////////////////////
Querie 2
Listar os N condutores com maior avaliação média. Em caso de empate, o resultado deverá ser
ordenado de forma a que os condutores com viagens mais recentes surjam primeiro
/////////////////////////*/
void querie2(char *out, char str[], ValidDriver *drivers, int t_d, int n,int show,int ncommand){
    printf("A executar a Query2...\n");
    FILE *ficheiro = fopen(out, "w");
	char *aux;
    ValidDriver d;

    if(n > 0 && n <= t_d){
        for(int i = 0; i < n; i++){
            d = drivers[i];
			aux = get_fullid(get_validDriver_id(d));
            sprintf(str,"%s;%s;%.3f\n",aux,get_validDriver_name(d), get_validDriver_avmedia(d)/get_validDriver_nviagens(d)); 
            fputs(str,ficheiro);
            if(show == 1)printf("Linha %d: %s",i+1,str);
			free(aux);
        }
    }

	fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

//função que retorna o top n de utilizadores
void querie3(char *out, char str[], ValidUser *users, int t_u, int n,int show,int ncommand){
    printf("A executar a Query3...\n");
    FILE *ficheiro = fopen(out, "w");
    ValidUser u;
    
    if(n > 0 && n < t_u){
        for(int i = 0; i < n ; i++){
            u = users[i];
            sprintf(str,"%s;%s;%d\n",get_validUser_id(u),get_validUser_name(u), get_validUser_totaldistance(u)); 
            fputs(str,ficheiro);
            if(show == 1)printf("Linha %d: %s",i+1,str);
        }
    }

	fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}


/*//////////////////////////
Querie 4
Preço médio das viagens (sem considerar gorjetas) numa determinada cidade, representada
por <city>. 
/////////////////////////*/
void querie4(char *out, char str[], Ride *auxride, int t_r, char *city,int show,int ncommand){
    printf("A executar a Query4...\n");
    FILE *ficheiro = fopen(out, "w");

    double media = 0;
	int j = 0;
    Ride r;

	for(int i=0; i < t_r ;i++){
        r = auxride[i];
		if(strcmp(get_ride_city(r),city) == 0){
			media += get_ride_custo(r);
			j++;
		}
	}

    if(j > 0){
        sprintf(str,"%.3f\n",media/j);
        fputs(str,ficheiro);
        if(show == 1)printf("Preço médio na cidade de %s é: %s",city,str);
    }

    fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

/*//////////////////////////
Querie 5
Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo, sendo esse
intervalo representado por <data A> e <data B>
/////////////////////////*/
void querie5(char *out, char str[], Ride *auxride, int t_r, char *data1,char *data2,int show,int ncommand){
    printf("A executar a Query5...\n");
    FILE *ficheiro = fopen(out, "w");

    double media = 0;
	int j = 0, d1 = dateInt(data1), d2 = dateInt(data2);
    Ride r;
	
	for(int i=0; i < t_r ;i++){
        r = auxride[i];
		if((get_ride_date(r) >= d1) && (get_ride_date(r) <= d2)){
			media += get_ride_custo(r);
			j++;
		}
	}

    if(j > 0){
        sprintf(str,"%.3f\n",media/j);
        fputs(str,ficheiro);
        if(show == 1)printf("O preço médio entre as datas %s e %s é: %s",data1,data2,str);
    }

    fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

/*//////////////////////////
Querie 6
Distancia media das viagens numa dada cidade num dado intervalo de tempo, sendo esse
intervalo representado por <data A> e <data B>
/////////////////////////*/
void querie6(char *out, char str[], Ride *auxride, int t_r, char* city,char *data1,char *data2,int show,int ncommand){
    printf("A executar a Query6...\n");
    FILE *ficheiro = fopen(out, "w");

    double dist = 0;
	int j = 0, d1 = dateInt(data1), d2 = dateInt(data2);
    Ride r;
	
	for(int i=0; i < t_r ;i++){
        r = auxride[i];
		if((get_ride_date(r) >= d1) && (get_ride_date(r) <= d2) && strcmp(city,get_ride_city(r)) == 0){
			dist += get_ride_distance(r);
			j++;
		}
	}

    if(j > 0){
        sprintf(str,"%.3f\n", dist/j);
        fputs(str,ficheiro);
        if(show == 1)printf("A distancia média das viagens entre %s e %s em %s é: %s",data1,data2,city,str);
    }

    fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

/*//////////////////////////
Querie 7
Top N condutores numa determinada cidade, representada por <city> (no ficheiro rides.csv),
ordenado pela avaliação média do condutor. Em caso de empate, o resultado deverá ser ordenado
através do id do condutor, de forma decrescente. A avaliação média de um condutor numa cidade é
referente às suas viagens nessa cidade, e não na cidade que está no seu pefil (ou seja, o mesmo
condutor poderá ter médias diferentes dependendo da cidade).
/////////////////////////*/
void querie7(char *out, char str[], DriverCity *dcity,int t_dc, char *city,int n,int show,int ncommand){
    printf("A executar a Query7...\n");
    FILE *ficheiro = fopen(out, "w");
    
    char *aux;
    DriverCity dc;
    
    if(n > 0){
        int j=0;
        for(int i=0; j < n && i < t_dc ; i++){
            dc = dcity[i];
            if(strcmp(get_drivercity_city(dc),city) == 0){
                aux = get_fullid(get_drivercity_id(dc));
                sprintf(str,"%s;%s;%.3f\n", aux, get_drivercity_name(dc), get_drivercity_score(dc)/get_drivercity_n(dc)); 
                fputs(str,ficheiro);
                if(show == 1)printf("Linha %d: %s",j+1,str);
                j++;
                free(aux);
            }
        }
    }
	fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

/*//////////////////////////
Querie 8
Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro, 
representado por <gender> e têm pefis com X ou mais anos, sendo X representado
por <X>. O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro,
mais especificamente, ordenar por conta mais antiga de condutor e, se necessário, pela conta do
utilizador. Se persistirem empates, ordenar por id da viagem (em ordem crescente).
/////////////////////////*/
void querie8(char *out, char str[], Ride *rides ,int tamanho ,char gender,int age,int show,int ncommand, int last){
    printf("A executar a Query8...\n");
    int linha = 1;
    
    FILE *ficheiro = fopen(out, "w");
	char *aux;
    Ride r;

	if(last != 8){
		ordenaValidos(rides,0,tamanho-1);
		last = 8;
	}

    for(int i=0 ; i < tamanho ;i++){
        r = rides[i];
        if((get_ride_genero(r) == gender) && (get_age(get_ride_accAgeUser(r)) >= age) && (get_age(get_ride_accAgeDriver(r)) >= age)){
            aux = get_fullid(get_ride_id(r));
			sprintf(str,"%s;%s;%s;%s\n", aux, get_ride_drivername(r), get_ride_idUser(r), get_ride_username(r)); 
            fputs(str,ficheiro);
            if(show == 1){
                printf("Linha %d: %s",linha,str);
                linha++;
            }
			free(aux);
        }
    }

	fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}

/*//////////////////////////
Querie 9
Listar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B),
sendo esse intervalo representado pelos parâmetros <data A> e <data B>, ordenadas por ordem de
distância percorrida (em ordem decrescente). Em caso de empate, as viagens mais recentes deverão
aparecer primeiro. Se persistirem empates, ordenar pelo id da viagem (em ordem decrescente).
/////////////////////////*/

void querie9(char *out, char str[], Ride *rides, int tamanho,char* data1,char* data2, int show, int ncommand, int last){
    printf("A executar a Query9...\n");
    FILE *ficheiro = fopen(out, "w");

    int d1 = dateInt(data1),d2 = dateInt(data2),linha = 1;
	char *aux, *aux2;
    Ride r;

	if(last != 9){
		ordenaRides(rides,0,tamanho-1);
		last = 9;
	}

	for(int j=0 ; j < tamanho ; j++){
        r = rides[j];
        if((get_ride_date(r) >= d1) && (get_ride_date(r) <= d2) && get_ride_tip(r) > 0){
			aux = get_fullid(get_ride_id(r));
			aux2 = dateChar(get_ride_date(r));
            sprintf(str,"%s;%s;%d;%s;%.3f\n", aux, aux2 , get_ride_distance(r), get_ride_city(r), get_ride_tip(r)); 
            fputs(str,ficheiro);
            if(show == 1){
                printf("Linha %d: %s",linha,str);
                linha++;
            }
			free(aux);
			free(aux2);
        }
    }

	fclose(ficheiro);
    printf("Ficheiro de saída fechado e comando número %d concluído.\n",ncommand);
}
