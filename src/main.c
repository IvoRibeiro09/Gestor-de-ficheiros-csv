#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include "../include/parser.h"
#include "../include/users.h"
#include "../include/validUser.h"
#include "../include/drivers.h"
#include "../include/validDriver.h"
#include "../include/rides.h"
#include "../include/query.h"
#include "../include/queryaux.h"
#include "../include/driver_ride.h"
#include "../include/driverCity.h"
#include <stdio.h>
#include <time.h>
/*
//threads
int t_rides, t_driveride, t_users, t_drivers;
// Define a structure to hold the arguments for each thread
struct ThreadArgs {
    Cat_Users cat_users;
    Cat_Drivers cat_drivers;
    Cat_Driver_Ride cdr;
    char *dataset;
};

void *executeNewRides(void *args) {
   	struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
	
	t_rides = new_rides(threadArgs->cat_users, threadArgs->cat_drivers, threadArgs->cdr, threadArgs->dataset);

    return NULL;
}

void *executeNewDriveride(void *args) {
   	struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
	
	t_driveride = new_driverride(threadArgs->cdr);

    return NULL;
}

void *executeNewUsers(void *args) {
   	struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
	
	t_users = new_user(threadArgs->cat_users);
	
    return NULL;
}

void *executeNewDrivers(void *args) {
   	struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
	
	t_drivers = new_driver(threadArgs->cat_drivers);
	
    return NULL;
}
	// Create threads for each function
	
    struct ThreadArgs argss = {cat_users, cat_drivers, cdr, dataset};
    pthread_t thread[4];
    int result0 = pthread_create(&(thread[0]), NULL, executeNewDriveride, &argss);
    int result1 = pthread_create(&(thread[1]), NULL, executeNewRides, &argss);
    int result2 = pthread_create(&(thread[2]), NULL, executeNewUsers, &argss);
    int result3 = pthread_create(&(thread[3]), NULL, executeNewDrivers, &argss);
    

    if (result0) {
        printf("Erro ao criar a thread: %d\n", result0);
        exit(-1);
    }
	if (result1) {
        printf("Erro ao criar a thread: %d\n", result1);
        exit(-1);
    }
	if (result2) {
        printf("Erro ao criar a thread: %d\n", result2);
        exit(-1);
    }
	if (result3) {
        printf("Erro ao criar a thread: %d\n", result3);
        exit(-1);
    }

    // Aguarde a conclusão da thread
    pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	pthread_join(thread[3], NULL);
*/
/*
int main() {
    clock_t inicio, fim;
    double tempo_decorrido;

    // Registra o tempo inicial
    inicio = clock();

    // Chama a função que você deseja medir
    funcao_que_quer_medir();

    // Registra o tempo final
    fim = clock();

    // Calcula o tempo decorrido
    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo decorrido: %lf segundos\n", tempo_decorrido);

    return 0;
}
*/

int main(int argc, char** argv) {

	clock_t inicio, fim;
    double tempo_decorrido;

	// Registra o tempo inicial
    inicio = clock();
	printf(".....................LOADING.....................\n");
	write(STDOUT_FILENO,"####",5);

	if (argc < 2) {
		printf("Error. Not enough arguments.\n");
	}

	char *dataset = argv[1];
	char *input = argv[2];

	//criar as hashtables para facilitar inserçao dos valores

	Cat_Users cat_users = create_user_cat();
	Cat_Drivers cat_drivers = create_driver_cat();
	Cat_Driver_Ride cdr = create_driver_ride_cat();
	write(STDOUT_FILENO,"########",9);
	

	//preencher as hashtables
		
	parser_users(cat_users, dataset);
	parser_drivers(cat_drivers, dataset);	

	//fazer novos ficheiros so com os elementos validos das 4 estruturas que usamos
	int t_rides = new_rides(cat_users, cat_drivers,cdr,dataset);
	//printf("\n\nnovo ficheiro de rides criado com %d linhas\n",t_rides);
	write(STDOUT_FILENO,"####",5);

	int t_driveride = 0;

	t_driveride = new_driverride(cdr);
	//printf("novo ficheiro de driverrides criado com %d linhas\n",t_driveride);
	write(STDOUT_FILENO,"####",5);
	int t_users = new_user(cat_users);
	//printf("novo ficheiro de users criado com %d linhas\n",t_users);
	write(STDOUT_FILENO,"####",5);
	int t_drivers = new_driver(cat_drivers);
	//printf("novo ficheiro de drivers criado com %d linhas\n",t_drivers);
	write(STDOUT_FILENO,"####",5);

	//eleminar todas as hashtables para nao ficarmos com nada em memoria

	free_cat_driver_ride(cdr);
	//printf("hashtable dos driversrides eliminada\n");
	free_cat_users(cat_users);
	//printf("hashtable dos users eliminada\n");
	free_cat_drivers(cat_drivers);
	//printf("hashtable dos drivers eliminada\n");
	write(STDOUT_FILENO,"####",5);

	//ler os novos ficheiros e inserir nos arrays de estruturas 

	Ride *auxride = get_rides_list(t_rides);
	//printf("Lista de Rides criada com %d válidos\n",j);
	write(STDOUT_FILENO,"####",5);
	DriverCity *auxdc = get_drivercity_list(t_driveride);
	//printf("Lista de Driver_Rides criada com %d válidos\n",j);
	write(STDOUT_FILENO,"####",5);
	ValidUser *auxusers = get_users_list(t_users);
	//printf("Lista de Users ativos criada com %d válidos\n",j);
	write(STDOUT_FILENO,"####",5);
	ValidDriver *auxdriver = get_drivers_list(t_drivers);
	//printf("Lista de Drivers ativos criada com %d válidos\n",j);
	write(STDOUT_FILENO,"####\n",6);

	fim = clock();

	// Calcula o tempo decorrido
    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\tLoading time: %lf sec\n\n", tempo_decorrido);
	
	//fazer as queries 

	if (input) batchmode(auxusers, auxdriver, auxride,auxdc, t_users, t_drivers, t_rides, t_driveride, input);
	else iterativemode(auxusers, auxdriver, auxride, auxdc, t_users, t_drivers, t_rides, t_driveride);
	
	//libertar a memoria dos arrays de estruturas

	free_arrayuser(auxusers, t_users);
	//printf("free do array de users\n");
	free_arraydrivers(auxdriver, t_drivers);
	//printf("free do array de drivers\n");
	free_arrayrides(auxride, t_rides);
	//printf("free do array de rides\n");
	free_arraydr(auxdc, t_driveride);
	//printf("free do array de drivercity\n");
	
	// Registra o tempo final
    fim = clock();

	// Calcula o tempo decorrido
    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo decorrido: %lf segundos\n", tempo_decorrido);

	return 0;
}
