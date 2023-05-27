#ifndef __MAIN__H__
#define __MAIN__H__

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *_strtok(char *str, char *delims);
char **tokenize(char *str, char *delims);
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *prompt(void);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void *_realloc(void *ptr, size_t size);
void spawn(char *cmd, char **args);
int __exit(char *arg);
void _print_env(char **envp);
int lookup(char **command);

#endif
