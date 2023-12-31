#include "main.h"
#include <stdlib.h>
#include <unistd.h>
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
 * _put_error - prints error using write
 * @c: string pointer
 * Return: number of bytes written
 */
int _put_error(char *c)
{
	return (write(STDERR_FILENO, c, _strlen(c)));
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
/**
 * _custom_err - print to stdout a personnalized error msg.
 * @err_msg: from the genertor error
 * @msg: to be added manually.
 * Return: the new customized error message.
 */
char *_custom_err(char *err_msg, char *msg)
{
	err_msg = _realloc(err_msg, 100, 100 + _strlen(msg) + 1);
	_strcat(err_msg, ": ");
	_strcat(err_msg, msg);
	return (err_msg);
}
/**
 * _cd_err - print to stdout a personnalized error msg for cd to unknown dir.
 * @err_msg: from the genertor error
 * @msg: to be added manually.
 * @cmds: array of tokens/commands
 * Return: the new customized error message.
 */
char *_cd_err(char *err_msg, char *msg, char **cmds)
{
	err_msg = _realloc(err_msg, 100, 100 + _strlen(msg) + 1);
	_strcat(err_msg, ": ");
	_strcat(err_msg, msg);
	_strcat(err_msg, cmds[1]);
	_strcat(err_msg, "\n");
	return (err_msg);
}
