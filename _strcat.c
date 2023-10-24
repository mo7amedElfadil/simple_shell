#include "main.h"
/**
 * _strcat - function that concatenates two strings
 * Description: by appending the src string to the dest string,
 * overwriting the terminating null byte (\0)
 * at the end of dest, and then adds a terminating
 * null byte
 * @src: pointer to the source string.
 * @dest: pointer to the destination string.
 * Return: the pointer to destination.
 */
char *_strcat(char *dest, char *src)
{
	int l = 0, m = 0;

	for (; dest[l]; l++)
		;
	while (src[m])
	{
		dest[l + m] = src[m];
		m++;
	}
	dest[l + m] = 0;
	return (dest);
}


/**
 * _strncat - function that concatenates two strings
 * Description: by appending the n bytes from src string to the dest string,
 * overwriting the terminating null byte (\0)
 * at the end of dest, and then adds a terminating
 * null byte unless src contains n or more bytes
 * @src: pointer to the source string.
 * @dest: pointer to the destination string.
 * @n: number of bytes taken from src
 * Return: the pointer to destination.
 */
char *_strncat(char *dest, char *src, int n)
{
	int l = 0, m = 0;

	for (; dest[l]; l++)
		;
	while (m < n && src[m])
	{
		dest[l + m] = src[m];
		m++;
	}
	dest[l + m] = 0;
	return (dest);
}
/**
 * strtow - splits a string into words.
 * @str: string to split
 * @del: delimter
 * Return: ptr to array of words (Success)
 *		   NULL (failure)
 */
char **strtow(char *str, char del)
{
	int words, i, l;
	char **ptr = NULL;

	words = word_count(str, del);
	if (!str || words == 0 || _strlen(str) == 0)
	{
		return (NULL);
	}
	ptr = (char **)malloc((words + 1) * sizeof(*ptr));
	for (i = 0; i < words && *str ; i++)
	{
		for (; *str && *str == del; str++)
		{
		}
		if (!*str)
			break;
		l = 0;
		while (str[l] != del && str[l])
		{
			l++;
		}


		ptr[i] = (char *)malloc((l + 1) * sizeof(**ptr));
		if (!ptr[i])
		{
			for (; i >= 0;)
				free(ptr[--i]);
			free(ptr);
			return (NULL);
		}
		_strncat(ptr[i], str, l);
		_strncat(ptr[i], "\n", l);
		str += l;
	}
	ptr[i] = NULL;

	return (ptr);
}
/**
 * word_count - function that counts number of words in a string,
 * @str: pointer to the string.
 * @del: delimter
 * Return: the number of words.
 */

int word_count(char *str, char del)
{
	int i, l, n = 0;
	char l_char;

	l = _strlen(str);
	l_char = str[0];
	for (i = 0; i <= l; i++)
	{
		if ((str[i] == del || str[i] == '\0') && l_char != del)
		{
			n++;
		}
		l_char = str[i];
	}
	return (n);
}
