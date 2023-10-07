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
	size_t len = 120;
	char *input = malloc(len), *token;
	char **cmds = malloc(sizeof(*cmds) * 10);

	(void)term_f;
	l = getline(&input, &len, stdin);
	if (l < 0 || !strncmp(input, "exit", 4))
	{
		if (l < 0 && term_f)
			_put_buffer("\n");
		free(input), free(cmds);
		fflush(stdin);
		return (-1);
	}
	x = strcspn(input, " ");
	cmds[i] = malloc(10);
	token =  strtok(input, " \t\r\n\v\f");
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
			cmds[i] = malloc(10), _strcpy(cmds[i], token);
		}
	}
	cmds[i + 1] = NULL;
	return (_execute(i, cmds, input, envp, av, counter));
}
/**
 * _execute - execute the commands
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 * @envp: environmental pointer
 * @av: argument vector
 * @counter: the counter
 * Return: -1 when execve fails
 *			0 otherwise
 */

int _execute(int span, char **cmds, char *input,
		char **envp, char **av, size_t counter)
{
	int status;
	pid_t pid;
	char *err_msg = NULL;

	pid = fork();
	if (pid == -1)
	{
		_frees_buff(span, cmds, input);
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(*cmds, cmds, envp);
		err_msg = _generate_error(cmds, av, counter);
		perror(err_msg);
		free(err_msg);
		_frees_buff(span, cmds, input);

		exit(EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error");
		_frees_buff(span, cmds, input);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		_frees_buff(span, cmds, input);
	return (EXIT_SUCCESS);
}

/**
 * _generate_error - generate error message
 * @counter: the counter
 * @cmds: array of tokens/commands
 * @av: argument vector
 * Return: error message
 */
char *_generate_error(char **cmds, char **av, size_t counter)
{
	char *err_msg = malloc(100), *ul = NULL;

	strcpy(err_msg, av[0]);
	strcat(err_msg, ": ");
	ul = _ultoa(counter);
	strcat(err_msg, ul);
	strcat(err_msg, ": ");
	strcat(err_msg, cmds[0]);
	free(ul);
	return (err_msg);
}
