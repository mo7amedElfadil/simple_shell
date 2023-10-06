#include "main.h"
/**
 * _ultoa - convert size_t to string
 * @x: size_t to convert to string
 * Return: converted string
 */
char *_ultoa(size_t x)
{
	size_t i = 0, buf = BUFF;
	char *y = NULL;

	y = _realloc(y, 0, buf);
	if (x == 0)
	{
		y[0] = '0', y[1] = '\0';
		return (y);
	}
	while (x !=  0)
	{
		y = ((i >= buf) ? _realloc(y, buf, buf + BUFF) : y);
		if (!y)
			free(y), perror("Error"), exit(98);
		buf = (i >= buf) ? buf + BUFF : buf;
		y[i] = x % 10 + 48;
		x /= 10;
		i++;
	}
	y = _realloc(y, buf, i + 1);
	y[i] = '\0';
	_rev_string(y);
	return (y);
}