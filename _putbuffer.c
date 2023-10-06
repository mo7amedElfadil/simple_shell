#include "main.h"
#include <stdio.h>
/**
 * _put_buffer - prints buffer using write
 * @c: string pointer
 * Return: number of bytes written
 */
int _put_buffer(char *c)
{
	return (write(stdout->_fileno, c, _strlen(c)));
}

/**
 * _put_error - prints error buffer using write to stderr1
 * @c: string pointer
 * Return: number of bytes written
 */
int _put_error(char *c)
{
	return (write(stderr->_fileno, c, _strlen(c)));
}

