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


