#include <stdio.h>
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



int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Error. Not enough arguments.\n");
	}

	char *dataset = argv[1];
	char *input = argv[2];

	//criar as hashtables para facilitar inserçao dos valores

	Cat_Users cat_users = create_user_cat();
	Cat_Drivers cat_drivers = create_driver_cat();
	Cat_Driver_Ride cdr = create_driver_ride_cat();

	//preencher as hashtables
		
	parser_users(cat_users, dataset);
	parser_drivers(cat_drivers, dataset);	

	//fazer novos ficheiros so com os elementos validos das 4 estruturas que usamos

	int t_rides = new_rides(cat_users, cat_drivers,cdr,dataset);
	printf("novo ficheiro de rides criado com %d linhas\n",t_rides);
	int t_driveride = new_driverride(cdr);
	printf("novo ficheiro de driverrides criado com %d linhas\n",t_driveride);
	int t_users = new_user(cat_users);
	printf("novo ficheiro de users criado com %d linhas\n",t_users);
	int t_drivers = new_driver(cat_drivers);
	printf("novo ficheiro de drivers criado com %d linhas\n",t_drivers);

	//eleminar todas as hashtables para nao ficarmos com nada em memoria

	free_cat_driver_ride(cdr);
	printf("hashtable dos driversrides eliminada\n");
	free_cat_users(cat_users);
	printf("hashtable dos users eliminada\n");
	free_cat_drivers(cat_drivers);
	printf("hashtable dos drivers eliminada\n");

	//ler os novos ficheiros e inserir nos arrays de estruturas 

	Ride *auxride = get_rides_list(t_rides);
	DriverCity *auxdc = get_drivercity_list(t_driveride);
	ValidUser *auxusers = get_users_list(t_users);
	ValidDriver *auxdriver = get_drivers_list(t_drivers);
	
	//fazer as queries 

	if (input) batchmode(auxusers, auxdriver, auxride,auxdc, t_users, t_drivers, t_rides, t_driveride, input);
	else iterativemode(auxusers, auxdriver, auxride, auxdc, t_users, t_drivers, t_rides, t_driveride);
	
	//libertar a memoria dos arrays de estruturas

	free_arrayuser(auxusers, t_users);
	printf("free do array de users\n");
	free_arraydrivers(auxdriver, t_drivers);
	printf("free do array de drivers\n");
	free_arrayrides(auxride, t_rides);
	printf("free do array de rides\n");
	free_arraydr(auxdc, t_driveride);
	printf("free do array de drivercity\n");
	

	return 0;
}
