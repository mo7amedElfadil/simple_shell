#include "main.h"
/**
 * _strcmp - compares n chars in both strings.
 * @s1: 1st string.
 * @s2: 2nd string.
 * Return: difference between the total value based on ASCII of both strings.
 * 0 if they match until n.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (*(s1 + i) == *(s2 + i) && *(s2 + i) != '\0' && *(s1 + i) != '\0')
	{
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}

/**
 * _strncmp - compares n chars in both strings.
 * @s1: 1st string.
 * @s2: 2nd string.
 * @n: number of chars to be campared.
 * Return: difference between the total value based on ASCII of both strings.
 * 0 if they match until n.
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (*(s1 + i) == *(s2 + i) && *(s2 + i) != '\0' && *(s1 + i) != '\0')
	{
		if (i >= n - 1)
			break;
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}
