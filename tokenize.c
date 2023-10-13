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
		exit_handler(line, term_f, cmds, envp, input);
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

