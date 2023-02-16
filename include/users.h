#ifndef USERS_
#define USERS_
#include <glib.h>
#include <stdbool.h>

typedef struct cat_users *Cat_Users;
typedef struct user *User;

User create_user(char **fields);

Cat_Users create_user_cat();

Cat_Users insert_user(char *key, User data, Cat_Users cat_users);

void insert_userinfo(char **fields, User user,double custoPorRide);

User search_user(char *key, Cat_Users cat_users);

int get_cat_users_length(Cat_Users cat_users);

char *get_user_id(User data);

char *get_user_name(User data);

char get_user_gender(User data);

int get_user_age(User data);

char get_user_accountstatus(User data);

int get_user_creationdate(User data);

int get_user_totaldistance(User data);

double get_user_avmedia(User data);

double get_user_totalgasto(User data);

int get_user_nviagens(User data);

int get_user_lastride(User data);

int new_user(Cat_Users cat_users);

void free_cat_users(Cat_Users cat_users);

void free_cat_users_func(gpointer key, gpointer value, gpointer data);

#endif
