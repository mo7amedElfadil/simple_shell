#include "main.h"
#include <stddef.h>

/**
 * _strspn - gets the length of a prefix substring
 * @s: pointer the a string.
 * @accept: pointer to a string to find in s
 * Return: number of bytes in the initial segment of s which consist only
 * of bytes from accept.
 */
unsigned int _strspn(char *s, char *accept)
{
	int i = 0, j, sum = 0;

	if (*(accept + 0) == '\0' || *(s + 0) == '\0')
		return (sum);

	while (*(s + i))
	{
		j = 0;
		while (*(accept + j))
		{
			if (*(s + i) == *(accept + j))
			{
				sum += 1;
				break;
			}
			j++;
		}
		if (*(accept + j) == '\0')
			break;
		i++;
	}
	return (sum);
}
