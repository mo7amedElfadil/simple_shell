#include "main.h"
/**
 * _put_buffer - prints buffer using write
 * @c: string pointer
 * Return: number of bytes written
 */
int _put_buffer(char *c)
{
	return (write(STDOUT_FILENO, c, _strlen(c)));
}

/**
 * _put_buff - prints buffer using write
 * @c: string pointer
 * Return: number of bytes written
 */
int _put_buff(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}


/**
 * _generate_error - generate error message
 * @counter: the counter
 * @cmds: array of tokens/commands
 * @av: argument vector
 * Return: error message
 */
char *_generate_error(char **cmds, char **av, size_t counter)
{
	char *err_msg = malloc(100), *ul = NULL;

	_strcpy(err_msg, av[0]);
	_strcat(err_msg, ": ");
	ul = _ultoa(counter);
	_strcat(err_msg, ul);
	_strcat(err_msg, ": ");
	_strcat(err_msg, cmds[0]);
	free(ul);
	return (err_msg);
}
