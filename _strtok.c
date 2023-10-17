#include "main.h"

/**
 * _strtok - custom implementation of strtok function.
 * @str: The string to be tokenized.
 * @delim: The delimiter characters.
 * Return: A pointer to the next token found in str.
 */

char *_strtok(char *str, const char *delim)
{
	static char *t_next;
	char *t_start, *t_end;
	int loc = 0;


	if (str != NULL)
	{
		loc = _strspn(str, (char *)delim);
		if (*(str + loc) == '\0')
			return (NULL);
		t_next = str + loc;
	}
	if (t_next == NULL)
		return (NULL);

	t_start = t_next;
	t_end = _strpbrk(t_next, (char *)delim);

	if (t_end != NULL)
	{
		*t_end = '\0';
		loc = _strspn(t_end + 1, (char *)delim);
		*(t_end + loc) = '\0';
		t_next = t_end + loc + 1;
	}
	else
	{
		t_next = NULL;
		return (NULL);
	}
	return (t_start);
}
