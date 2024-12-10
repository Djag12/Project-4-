# Compiler and flags
CC = gcc
CFLAGS = -lpthread -Wformat -Wall

# Server target
serv: serv.c list.c list.h
	$(CC) serv.c list.c $(CFLAGS) -o server

# Client target
cli: cli.c
	$(CC) cli.c $(CFLAGS) -o client
