#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list node
 * @num: the number field
 * @str: the string field
 * @next: pointer to the next node in the list
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - structure for passing arguments to a function
 * @arg: string containing arguments generated from getline
 * @argv: array of strings generated from arg
 * @path: string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()
 * @linecount_flag: flag indicating if this line of input should be counted
 * @fname: program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: flag indicating if environ was changed
 * @status: return status of the last executed command
 * @cmd_buf: address of pointer to cmd_buf, flag indicating if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: file descriptor from which to read line input
 * @histcount: history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 * struct builtin - structure for built-in command
 * @type: the type of the built-in command
 * @func: pointer to the function associated with the built-in command
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int freee(void **);

/* toem_atoi.c */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_isalpha(int);
int convert_to_int(char *);

/* toem_errors1.c */
int err_atoi(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* toem_builtin1.c */
int my_history(info_t *);
int my_alias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *get_env(info_t *, const char *);
int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environment(info_t *);
int unset_environment(info_t *, char *);
int set_environment(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
