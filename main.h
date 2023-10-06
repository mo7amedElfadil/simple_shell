#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
/* dont need these yet */
/* #include <errno.h> */
/* #include <signal.h> */

/* Important! Delete comment!! */
#ifndef BUFF
#define BUFF 1024
#endif
/* your protos goes here */
int _put_buffer(char *);
void _rev_string(char *s);
int _put_error(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strncat(char *dest, char *src, int n);
void _frees_buff(int span, char **cmds, char *input);
char *_strcpy(char *dest, char *src);
int _tokenize(int term_f, char **envp);
int _execute(int span, char **cmds, char *input, char **envp);
char *_itoa(int x);
char *_generate_error(char **cmds, int span);
#endif /* HEADER */
