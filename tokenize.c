#include "main.h"
#include <stdio.h>

/**
 * _tokenize - tokenize the input line
 * @term_f: terminal flag (isatty)
 * @envp: environmental pointer
 * @av: argument vector
 * @counter: the counter
 * Return: 1 when exit has been input
 *			0 otherwise
 */
int _tokenize(int term_f, char **envp, char **av, size_t counter)
{
	int i = 0, l = 0, x = 0;
	size_t len = BUFF;
	char *input = malloc(len), *token;
	char **cmds = malloc(sizeof(*cmds) * BUFF);

	(void)term_f;
	l = getline(&input, &len, stdin);
	if (l < 0 || !strncmp(input, "exit", 4))
	{
		if (l < 0 && term_f)
			_put_buffer("\n");
		x = exit_handler(input);
		free(input), free(cmds);
		fflush(stdin);
		exit(x);
		return (-1);
	}
	x = strcspn(input, " ");
	token =  strtok(input, " \t\r\n\v\f");
	cmds[i] = malloc(_strlen(token) + 1);
	if (!token)
	{
		_frees_buff(i, cmds, input);
		return (1);
	}
	_strcpy(cmds[i], token);
	if (x < l)
	{
		while (cmds[i])
		{
			i++;
			token = strtok(NULL, " \t\r\n\v\f");
			if (!token)
			{
				i--;
				break;
			}
			cmds[i] = malloc(_strlen(token) + 1), _strcpy(cmds[i], token);
		}
	}
	cmds[i + 1] = NULL;

	if (!term_f)
	{
		_execute(i, cmds, input, envp, av, counter);
		x =	_tokenize(term_f, envp, av, counter);
		return (x);

	}
		return (_execute(i, cmds, input, envp, av, counter));
}

int exit_handler(char* input)
{
	char *token;

	token = strtok(input, " \t\r\n\v\f");
	token = strtok(NULL, " \t\r\n\v\f");
	if (token)
	{
		return (_atoi(token));
	}
	return (0);

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
		if (*s == ';')
			break;
		if (*s == '-')
			n_count++;
		if (*s >= 48 && *s <= 57)
			num = (num * 10) + (*s - 48);
		s++;

	}

	return (n_count % 2 == 0 ? num : -num);
}
