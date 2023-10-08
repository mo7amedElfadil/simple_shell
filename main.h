#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stddef.h>
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

char *get_envalue(char *var, char **envp, int len);
int cd_cmd(int argc, char *argv[], char *envp[]);
char *cd_cmd_dd(char *en_v_PWD);
#endif /* HEADER */
