#include "main.h"

/**
 * _strchr - locates a character in a string.
 * @s: pointer the a string.
 * @c: character to find in s.
 * Return: a pointer to the first occurrence of the c in the string s,
 * or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (*(s + i) != c && *(s + i))
	{
		i++;
	}
	if (*(s + i) == c)
		return ((s + i));
	else
		return (0);
}
