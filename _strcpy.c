#include "main.h"
/**
 * _strcpy - function that copies the string pointed to by src,
 * Description: including the terminating null byte (\0),
 * to the buffer pointed to by dest.
 * @src: pointer to the source string.
 * @dest: pointer to the destination string.
 * Return: the pointer to destination.
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;

	while (src[l])
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = 0;
	return (dest);
}
/**
 * _memcpy - copies memory area
 * @dest: pointer to destination string buffer
 * @src: pointer to source string buffer
 * @n: number of bytes of memory to fill
 * Return: dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;
	char *ptrs = src;
	char *ptrd = dest;

	for (i = 0; i < n; i++, ptrs++, ptrd++)
	{
		*ptrd = *ptrs;
	}

	return (dest);
}


