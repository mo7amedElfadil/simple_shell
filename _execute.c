#include "main.h"
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
		char *token = NULL, *path = NULL;

		if (*cmds[0] != '.' && *cmds[0] != '/')
		{
			token = cmd_path(envp, cmds[0]);
			if (token)
			{
				path = malloc(_strlen(cmds[0]) + 1), _strcpy(path, cmds[0]);
				cmds[0] = _realloc(cmds[0], strlen(cmds[0]) + 1,
						_strlen(cmds[0]) + _strlen(token) + 2);
				_strcpy(cmds[0], token), _strcat(cmds[0], "/");
				_strcat(cmds[0], path), free(path);
			}
		}

		execve(*cmds, cmds, envp);
		err_msg = _generate_error(cmds, av, counter);
		perror(err_msg), errno = 0;
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


