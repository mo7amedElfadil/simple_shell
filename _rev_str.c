#include "main.h"
/**
 * _rev_string - function that reverses a string.
 * @s: pointer to a string.
 */
void _rev_string(char *s)
{
	int i = 0, l = 0;
	char temp;

	l = _strlen(s);
	while (i < l / 2)
	{
		temp = s[i];
		s[i] = s[l - i - 1];
		s[l - i - 1] = temp;
		i++;
	}
}
