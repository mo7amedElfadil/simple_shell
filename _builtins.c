#include "main.h"
#include <ctype.h>

/**
 * print_pid - prints pid of the shell process
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @envp: environmental pointer
 * Return: 0 on success.
 */
int print_pid(int span, char **cmds, char **envp)
{
	char *result = _itoa(getpid());

	make_void(3, span, **cmds, **envp);
	_put_buffer(result);
	free(result);
	_put_buffer("\n");
	return (0);
}
/**
 * print_err - prints errno of the shell process
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @envp: environmental pointer
 * Return: 0 on success.
 */
int print_err(int span, char **cmds, char **envp)
{
	char *result = _itoa(errno);

	make_void(3, span, **cmds, **envp);
	_put_buffer(result);
	free(result);
	_put_buffer("\n");
	return (0);
}

/**
 * make_void - void unused arguments.
 * @num: number of arguments to void.
 * Return: None.
 */
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
 * @term_f: terminal flag (isatty).
 * @span: indix of last elements in cmds.
 * @cmds: array of tokens/commands.
 * @envp: environmental pointer
 * @input: input string from getline().
 * @av: argv.
 * @counter: count how many cmd has been executed.
 * Return: exit 0 on success.
 */
void exit_handler(int line, int term_f, int span, char **cmds,
		char **envp, char *input, char **av, size_t counter)
{
	char *token = NULL;
	int ex = errno;

	if (line < 0 && term_f)
		_put_buffer("\n");
	if (line != -1 && input)
	{
		token = strtok(input, " \t\r\n\v\f");
		token = strtok(NULL, " \t\r\n\v\f");
	}
	if (token)
	{
		ex = _atoi(token);
		if (_isnumeric(token) || ex < 0)
		{
			char *ptr = "exit";

			ptr = _strcat(_custom_err(_custom_err(_generate_error(&ptr, av, counter),
						"Illegal number"), token), "\n");
			_put_error(ptr), free(ptr), ex = 2;
		}
	}
	if (envp)
		_free_envp(envp);
	if (cmds)
		_frees_buff(span, cmds, input);
	else if (!cmds)
		free(input);
	exit(ex);
}

