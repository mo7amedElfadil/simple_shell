#include "main.h"
/**
 * _strcat - function that concatenates two strings
 * Description: by appending the src string to the dest string,
 * overwriting the terminating null byte (\0)
 * at the end of dest, and then adds a terminating
 * null byte
 * @src: pointer to the source string.
 * @dest: pointer to the destination string.
 * Return: the pointer to destination.
 */
char *_strcat(char *dest, char *src)
{
	int l = 0, m = 0;

	for (; dest[l]; l++)
		;
	while (src[m])
	{
		dest[l + m] = src[m];
		m++;
	}
	dest[l + m] = 0;
	return (dest);
}


/**
 * _strncat - function that concatenates two strings
 * Description: by appending the n bytes from src string to the dest string,
 * overwriting the terminating null byte (\0)
 * at the end of dest, and then adds a terminating
 * null byte unless src contains n or more bytes
 * @src: pointer to the source string.
 * @dest: pointer to the destination string.
 * @n: number of bytes taken from src
 * Return: the pointer to destination.
 */
char *_strncat(char *dest, char *src, int n)
{
	int l = 0, m = 0;

	for (; dest[l]; l++)
		;
	while (m < n && src[m])
	{
		dest[l + m] = src[m];
		m++;
	}
	dest[l + m] = 0;
	return (dest);
}
