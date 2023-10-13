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
	int status, flag = 0;
	pid_t pid;
	char *err_msg = NULL;


	if (*cmds[0] != '.' && *cmds[0] != '/')
	{

		if ((flag = choose_mode(span, cmds, envp)))
		{
			_path_cat(envp, cmds);
			_put_buffer(*cmds);
			_put_buffer("\n");
		}
		else
		{

			_frees_buff(span, cmds, input);
		}
	}
	if (flag)
	{
		pid = fork();
		if (pid == -1)
		{
			_frees_buff(span, cmds, input), perror("Error");
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(*cmds, cmds, envp);

			err_msg = _generate_error(cmds, av, counter);
			perror(err_msg);
			free(err_msg);
			if (envp)
				_free_envp(envp);
			_frees_buff(span, cmds, input);
			exit(EXIT_FAILURE);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error"), _frees_buff(span, cmds, input);
			return (EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			_frees_buff(span, cmds, input);
		}
	}

	return (EXIT_SUCCESS);
}

/*
 * chose_mode - chose the execution mode
 */
int choose_mode(int span, char **cmds, char **envp)
{
	int i = 0, j = (!_strcmp(*cmds, "echo") &&
			(cmds[1] ?
			((!_strcmp(cmds[1], "$$") ^ !_strcmp(cmds[1], "$?")))
			? 1: 0: 0));
	_built builtins[] =
	{{"cd", cd_cmd}, {"$$", print_pid},{"$?", print_err},
		{"env", print_envp},{"setenv",_setenv_cmd},
		{"unsetenv", _unsetenv_cmd}, {"alias", alias},
		{NULL, NULL}};

	for (i = 0; builtins[i].cmd; i++)
	{
		if (!strcmp(cmds[j], builtins[i].cmd))
		{
			switch (i)
			{
				case 0:
					cd_cmd(span + 1, cmds, envp);
					return (EXIT_SUCCESS);
				case 1:
					print_pid(span, cmds, envp);
					return (0);
				case 2:
					print_err(span, cmds, envp);
					return (0);
				case 3:
					print_envp(span + 1, NULL, envp);
					return 0;
				case 4:
					_setenv_cmd(span + 1, cmds, envp);
					return 0;
				case 5:
					_unsetenv_cmd(span + 1, cmds, envp);
					return 0;
				case 6:
					alias(span, cmds, envp);
					return 0;
			}
		}
	}
	return (1);
}



