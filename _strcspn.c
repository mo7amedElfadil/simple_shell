#include "main.h"

/**
 * _strcspn - calculates the length of the number of characters in string s1
 * 	before the 1st occurrence of character present in string s2.
 * @s1: The Target string in which search has to be made.
 * @s2: Argument string containing characters to match in target string.
 * Return: the number of characters in s1 before the 1st occurrence of character
 * 	present in both the string.
 */

int _strcspn(char *s1, char *s2)
{
	int i = 0, j = 0;

	while (*(s1 + i))
	{
		j = 0;
		while (*(s2 + j ) && *(s1 + i) && *(s2 + j) != *(s1 + i))
			j++;
		if (*(s2 + j) == *(s1 + i))
			return (i);
		i++;
	}
	return (i);
}
