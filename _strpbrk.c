#include "main.h"
#include <stddef.h>

/**
 * _strpbrk - function locates the first occurrence in the string s of
 * any of the bytes in the string accept
 * @s: pointer the a string.
 * @accept: pointer to a string to find in s
 * Return: a pointer to the first occurrence of the accept in the string s,
 * or NULL if the character is not found.
 */
char *_strpbrk(char *s, char *accept)
{
	char *p = NULL;
	int i = 0, j;

	if (*(accept + 0) == '\0' || *(s + 0) == '\0')
		return (p);

	while (*(s + i))
	{
		j = 0;
		while (*(s + i) != *(accept + j) && *(accept + j))
		{
			j++;
		}
		if (*(s + i) == *(accept + j))
		{
			p = (s + i);
			break;
		}
		i++;
	}
	return (p);
}
