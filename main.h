#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
/*extern enviroment variable*/
extern char **environ;
/*Helper functions*/
void prompt(void);
char **sp_string(char *string, char *del);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *string, char *stradd);
char *_strdup(const char *str);
int _strlen(char *str);
int child(char **array, char *av[], int cont);
/*free functions*/
void free_arraybid(char **array);

/*environment*/
int print_env(void);

/*Exit*/
int _atoi(char *s);
int _isdigit(int c);
int exit_cmd(char **array, char *av[], char *line, int cont, int ret_status);

void manage_signal(int num_s __attribute__((unused)));

/*Errors*/
void print_errors(char **array, char *av[], int cont, int num);
int print_integer(int n);
int recursion_int(int n, int cont);
int _putchar(char c);
#endif
