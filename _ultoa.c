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

	y = malloc(buf);
	if (x == 0)
	{
		y[0] = '0', y[1] = '\0';
		return (y);
	}
	while (x !=  0)
	{
		y = ((i >= buf) ? _realloc(y, buf, buf + BUFF) : y);
		if (!y)
		{
			free(y);
			return (NULL);
		}
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

/**
 * _itoa - convert integer to string
 * @x: integer to convert to string
 * Return: converted string
 */
char *_itoa(int x)
{
	int i = 0, neg = 0, buf = BUFF;
	char *y = NULL;

	y = _realloc(y, 0, buf);
	if (x == 0)
	{
		y[0] = '0', y[1] = '\0';
		return (y);
	}
	else if (x < 0)
	{
		neg = 1, x++, x = -x, i++;
		y[0] = x % 10 + 48 + 1;
		x = x / 10;
	}
	while (x > 0)
	{
		y = ((i >= buf) ? _realloc(y, buf, buf + BUFF) : y);
		if (!y)
			free(y), exit(98);
		buf = (i >= buf) ? buf + BUFF : buf;
		y[i] = x % 10 + 48;
		x /= 10;
		i++;
	}
	if (neg == 1)
	{
		y = ((i >= buf) ? _realloc(y, buf, buf + BUFF) : y);
		if (!y)
			free(y), exit(98);
		buf = (i >= buf) ? buf + BUFF : buf;
		y[i] = '-';
		i++;
	}
	y = _realloc(y, buf, i + 1);
	y[i] = '\0';
	_rev_string(y);
	return (y);
}
/**
 * _atoi - converts string to an integer
 * @s: string pointer
 *
 * Return: 0 if there're no numbers in the string,
 * otherwise return the integer
 */
int _atoi(char *s)
{
	unsigned int num = 0, n_count = 0;

	while (*s)
	{
		if (*s == '-')
			n_count++;
		if (*s >= 48 && *s <= 57)
			num = (num * 10) + (*s - 48);
		s++;

	}

	return (n_count % 2 == 0 ? num : -num);
}

/**
 * _isalpha - checks for alphabetical characters.
 * @c: character to test if is alphabetical
 * Return: 1 (Success if character is alphabetical)
 *		   0 (Failure if character is not alphabetical)
 */
int _isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/**
 * _isnumeric - checks if a string is a digit
 * @c: string to be tested
 * Return:  0 (Success)
 *			1 (Failure)
 */
int _isnumeric(char *c)
{
	while (*c)
	{
		if (*c < 48 || *c > 57)
			return (1);
		c++;
	}
	return (0);
}
