#include "main.h"
/**
 * _tokenize - tokenize the input line
 * @term_f: terminal flag (isatty)
 * @envp: environmental pointer
 * Return: 1 when exit has been input
 *			0 otherwise
 */
int _tokenize(int term_f, char **envp)
{
	int i = 0, j = 0;
	size_t len = 120, l = 0, x = 0;
	char *input = malloc(len), *token;
	char **cmds = malloc(sizeof(*cmds) * 10);

	i = 0, j = 0;
	l = getline(&input, &len, stdin);
	if (!strncmp(input, "exit", 4))
	{
		free(input), free(cmds);
		return (-1);
	}
	x = strcspn(input, " ");
	cmds[i] = malloc(10);
	token =  strtok(input, " \t\r\n\v\f");
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
			cmds[i] = malloc(10);
			_strcpy(cmds[i], token);
		}
	}
	cmds[i + 1] = NULL;
	return (_execute(i, cmds, input, envp));
}
/**
 * _execute - execute the commands
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 * @envp: environmental pointer
 * Return: -1 when execve fails
 *			0 otherwise
 */

int _execute(int span, char **cmds, char *input, char **envp)
{
	int pid, status;

	pid = fork();
	if (pid == -1)
	{
		_put_error("fork failed");
		_frees_buff(span, cmds, input);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(*cmds, cmds, envp);
		_frees_buff(span, cmds, input);
		exit(1);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		_put_error("waitpid failed");
		_frees_buff(span, cmds, input);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		_frees_buff(span, cmds, input);
	return (EXIT_SUCCESS);
}
