#Compiler
CC = gcc

#Compiler flags
CCFLAGS = -Wall -g -pg

#GLIB flag
PKG_CONFIG = `pkg-config --cflags --libs glib-2.0`

#Source files
SRC = src/driver_ride.c src/validDriver.c src/validUser.c src/driverCity.c src/drivers.c src/main.c src/parser.c src/queryaux.c src/query.c src/rides.c src/users.c

#Object Files
OBJ = obj/driver_ride.o obj/validDriver.o obj/validUser.o obj/driverCity.o obj/drivers.o obj/main.o obj/parser.o obj/queryaux.o obj/query.o obj/rides.o obj/users.o

all: main

obj/main.o : src/main.c
		gcc -c src/main.c -o obj/main.o ${PKG_CONFIG}

obj/driver_ride.o : src/driver_ride.c
		gcc -c src/driver_ride.c -o obj/driver_ride.o ${PKG_CONFIG}


obj/drivers.o : src/drivers.c
		gcc -c src/drivers.c -o obj/drivers.o ${PKG_CONFIG}
		

obj/validDriver.o : src/validDriver.c
		gcc -c src/validDriver.c -o obj/validDriver.o ${PKG_CONFIG}


obj/validUser.o : src/validUser.c
		gcc -c src/validUser.c -o obj/validUser.o ${PKG_CONFIG}


obj/driverCity.o : src/driverCity.c
		gcc -c src/driverCity.c -o obj/driverCity.o ${PKG_CONFIG}


obj/parser.o : src/parser.c
		gcc -c src/parser.c -o obj/parser.o ${PKG_CONFIG}


obj/queryaux.o : src/queryaux.c
		gcc -c src/queryaux.c -o obj/queryaux.o ${PKG_CONFIG}


obj/query.o : src/query.c
		gcc -c src/query.c -o obj/query.o ${PKG_CONFIG}


obj/rides.o : src/rides.c
		gcc -c src/rides.c -o obj/rides.o ${PKG_CONFIG}


obj/users.o : src/users.c
		gcc -c src/users.c -o obj/users.o ${PKG_CONFIG}

main: obj/main.o obj/driver_ride.o obj/validUser.o obj/driverCity.o obj/drivers.o obj/validDriver.o obj/parser.o obj/queryaux.o obj/query.o obj/rides.o obj/users.o
		$(CC) $(CCFLAGS) $(OBJ) -o programa-principal -g ${PKG_CONFIG}

clean:
		rm -r programa-principal obj/*.o Resultados/*
