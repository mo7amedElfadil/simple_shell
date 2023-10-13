#include "main.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_pid - prints pid of the shell process
 */
int print_pid(int span, char **cmds, char **envp)
{
	char *result = _itoa(getppid());

	make_void(3, span, **cmds, **envp);
	_put_buffer(result);
	free(result);
	_put_buffer("\n");
	return (0);
}
/**
 * print_err - prints errno of the shell process
 */
int print_err(int span, char **cmds, char **envp)
{
	char *result = _itoa(errno);

	make_void(3, span, **cmds, **envp);
	_put_buffer(result);
	free(result);
	_put_buffer("\n");
	errno = 0;
	return (0);
}

/**
 * alias - prints the aliases or creates new one or modifies existing
 */
int alias(int span, char **cmds, char **envp)
{
	char *result = _itoa(errno);
	make_void(3, span, cmds, envp);
	_put_buffer(result);
	free(result);
	_put_buffer("\n");
	return (0);
}

void make_void(int num, ...)
{
	va_list ap;

	va_start(ap, num);
	while (num > 0)
	{
		(void)va_arg(ap, void *);
		num--;
	}
	va_end(ap);

}

/**
 * exit_handler - Handles exit status
 * @line: return value of getline. Determines its exit status
 *		and used to know if ctrl + d or EOF was entered
 * @term_f: terminal flag (isatty)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 */
void exit_handler(int line, int term_f, char **cmds, char **envp, char *input)
{
	char *token = NULL;
	int ex = 0;

	if (line < 0 && term_f)
		_put_buffer("\n");
	if (line != -1)
	{
		token = strtok(input, " \t\r\n\v\f");
		token = strtok(NULL, " \t\r\n\v\f");
	}
	if (token)
		ex = _atoi(token);
	free(input), free(cmds), _free_envp(envp);
	exit(ex);
}

