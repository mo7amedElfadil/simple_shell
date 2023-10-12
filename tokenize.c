#include "main.h"

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
	int i = 0, line = 0, delimited = 0;
	size_t len = BUFF;
	char *input = malloc(len), *token;
	char **cmds = malloc(sizeof(*cmds) * BUFF);

	line = getline(&input, &len, stdin);
	if (line < 0 || !strncmp(input, "exit", 4))
		exit_handler(line, term_f, cmds, input);
	delimited = strcspn(input, " "); /* replace function with custom */
	token =  strtok(input, " \t\r\n\v\f");
	if (!token)
	{
		_frees_buff(-1, cmds, input);
		return (1);
	}
	cmds[i] = malloc(_strlen(token) + 1);
	_strcpy(cmds[i], token);
	if (delimited < line)
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
			printf("%s\n", cmds[i]);
		}
	}
	cmds[i + 1] = NULL;
	if (!term_f)
	{
		_execute(i, cmds, input, envp, av, counter);
		return (_tokenize(term_f, envp, av, counter));
	}
		return (_execute(i, cmds, input, envp, av, counter));
}

/**
 * exit_handler - Handles exit status
 * @line: return value of getline. Determines its exit status
 *		and used to know if ctrl + d or EOF was entered
 * @term_f: terminal flag (isatty)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 */
void exit_handler(int line, int term_f, char **cmds, char *input)
{
	char *token = NULL;
	int ex = 0;

	if (line < 0 && term_f)
		_put_buffer("\n");
	if (line != -1)
	{
		token = strtok(input, " \t\r\n\v\f");
		token = strtok(NULL, " \t\r\n\v\f");
	}
	if (token)
		ex = _atoi(token);
	free(input), free(cmds);
	exit(ex);
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


