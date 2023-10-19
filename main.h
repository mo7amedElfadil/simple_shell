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


/**
 * struct list_t - linked list's struct for alias function.
 * @value: string cmd for the command
 * @name: the name of the alias.
 * @next: pointer to next struct of a singly linked list.
 */
typedef struct list_t
{
	char *name;
	char *value;
	struct list_t *next;
} al_list;


/**
 * struct _builtin - builtin function struct
 * @cmd: string specifier
 */
typedef struct _builtin
{
	char *cmd;
} _built;

/* your protos goes here */
int _put_buffer(char *);
int _put_error(char *);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void _rev_string(char *s);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strstr(char *haystack, char *needle);
char *_strncat(char *dest, char *src, int n);
char *_memcpy(char *dest, char *src, unsigned int n);
char *_strcpy(char *dest, char *src);
int _strcspn(char *s1, char *s2);

void _frees_buff(int span, char **cmds, char *input);
void _free_envp(char **envp);
void _free_cd(int n, ...);
int is_nulled(char **cmds);

int _tokenize(int term_f, char **envp, char **av, size_t counter);
int _tokenize_newline(int *line, int term_f,
		char **envp, char **av, size_t counter);
char **_tokenize_n_al(int line, char *input, char **envp);
char *var_expansion(char *var, char **envp);
int cmds_n_elm(char **cmds);


char *cmd_path(char **envp, char *cmd);
int _path_cat(char **envp, char **cmds);
char *cut_prefix(char *cmds, int size);
char *prepend_pwd(char *cmds, char **envp);
int comment(char *token);

int _execute(int span, char **cmds, char *input,
		char **envp, char **av, size_t counter, int term_f);
int exec_fork(pid_t pid, int *status, char *err_msg, int span, char **cmds,
		char **envp, char *input, char **av, size_t count);

int check_echo(char **cmds);
char *_strtok(char *str, const char *delim);
char *_strpbrk(char *s, char *accept);
unsigned int _strspn(char *s, char *accept);



char *_ultoa(size_t x);
int _atoi(char *s);
char *_itoa(int x);
int _isalpha(int c);
int _isnumeric(char *c);
int is_cmd(char *cmd, char *cmd_name);


char *_generate_error(char **cmds, char **av, size_t counter);
char *_custom_err(char *err_msg, char *msg);


void exit_handler(int line, int term_f, int span,
		char **cmds, char **envp, char *input, char **av, size_t counter);


int cd_cmd(int argc, char *argv[], char *envp[]);
char *cd_cmd_dd(char *en_v_PWD);
int cd_cmd__(char *target, char *previous, char **envp, int a);
int cd_cmd_sup(char *target, char *previous, char **envp);
int is_v_path(const char *path);
int cd_cmd_par(char *target, char **envp);
char *get_envalue(char *var, char **envp, int len);


int _setenv_cmd(int argc, char **argv, char **envp);
int _setenv(char *var, char *val, int owr, char **envp);
int _unsetenv(char *var, char **envp);
int print_envp(int span, char **var, char **envp);
int _unsetenv_cmd(int argc, char **argv, char **envp);
char **copy_envp_main(char **envp);
int _put_buff(char c);

void make_void(int num, ...);
int choose_mode(int span, char **cmds, char **envp);

int print_pid(int span, char **cmds, char **envp);

int print_err(int span, char **cmds, char **envp);
char *alias(int span, char **cmds, char **envp);
al_list *add_node_linked_list(al_list **head, char *nam, char *val);
void print_linked_list(char *name, al_list *head);
void free_linked_list(al_list *head);
char *_list_value(al_list *head, char *name);

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
#endif /* HEADER */


