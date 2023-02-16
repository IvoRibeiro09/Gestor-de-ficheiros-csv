#ifndef DRIVERCITY_
#define DRIVERCITY_


typedef struct drivercity *DriverCity;

DriverCity drivercity_create(char **fields);

int get_drivercity_id(DriverCity data);

char *get_drivercity_city(DriverCity data);

char *get_drivercity_name(DriverCity data);

double get_drivercity_score(DriverCity data);

int get_drivercity_n(DriverCity data);

DriverCity *get_drivercity_list(int tamanho);

void ordenaDriverRides(DriverCity arr[], int l, int r);

void mergeaux7(DriverCity arr[],int l,int m,int r);

void free_arraydr(DriverCity *arr, int t);

#endif