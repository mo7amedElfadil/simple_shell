#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <dirent.h>
#include <stddef.h>

#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

/* dont need these yet */
/* #include <errno.h> */
/* #include <signal.h> */

/* Important! Delete comment!! */
#ifndef BUFF
#define BUFF 120
#endif
/* your protos goes here */
int _put_buffer(char *);
void _rev_string(char *s);
int _put_error(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strstr(char *haystack, char *needle);
char *_strncat(char *dest, char *src, int n);
void _frees_buff(int span, char **cmds, char *input);
char *_strcpy(char *dest, char *src);
int _tokenize(int term_f, char **envp, char **av, size_t counter);
char *cmd_path(char **envp, char *cmd);
void _path_cat(char **envp, char **cmds);
int _execute(int span, char **cmds, char *input,
		char **envp, char **av, size_t counter);
char *_ultoa(size_t x);
char *_generate_error(char **cmds, char **av, size_t counter);
void exit_handler(int line, int term_f, char **cmds, char *input);
int _atoi(char *s);

char *_itoa(int x);
int cd_cmd(int argc, char *argv[], char *envp[]);
char *cd_cmd_dd(char *en_v_PWD);
int cd_cmd__(char *target, char *previous, char **envp);
int cd_cmd_sup(char *target, char *previous, char **envp);
int is_v_path(const char *path);
int cd_cmd_par(char *target, char **envp);
char *get_envalue(char *var, char **envp, int len);


int _setenv_cmd(int argc, char **argv, char **envp);
int _setenv(char *var, char *val, int owr, char **envp);
int _unsetenv(char *var, char **envp);
void print_envp(char **envp, char *var);
int _unsetenv_cmd(int argc, char **argv, char **envp);
char **copy_envp_main(char **envp);
int _put_buff(char c);


void make_void(int num, ...);
int choose_mode(int span, char **cmds, char **envp);

int print_pid(int span, char **cmds, char **envp);

int print_err(int span, char **cmds, char **envp);
void alias(char **cmds, int span);
/**
 * struct _builtin - builtin function struct
 * @cmd: string specifier
 * @func: function pointer
 */
typedef struct _builtin
{
	char *cmd;
	int (*func)(int , char **, char **);
} _built;

/* int (*)(int,  char **, char **) */
/**
 * struct _intptr - void struct
 * @c: character specifier
 * @func: function pointer
 */
typedef struct _intptr
{
	char *c;
	void *(*func)(int *, char *);
} _ip;


#ifndef LIST_H
#define LIST_H
/**
 * struct list_cmd - singly linked list
 * @cmd: pointer to  char.
 * @linker: pointer to  char.
 * @next: points to struct(next node).
 *
 * Description: singly linked list node structure
 */
typedef struct list_cmd
{
	char *cmd;
	char *linker;
	struct list_cmd *next;
} list_c;


/* Function prototypes */
size_t print_list(list_c *h);
list_c *add_node(list_c **head, char *str);
list_c *add_node_end(list_c **head, char *str);
void free_list(list_c *head);
list_c *add_nodeint(list_c **head, int n);


#endif /* LIST_H */



#endif /* HEADER */


