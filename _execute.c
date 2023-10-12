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

	pid = fork();
	if (pid == -1)
	{
		_frees_buff(span, cmds, input);
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (*cmds[0] != '.' && *cmds[0] != '/')
		{
			if ((flag = choose_mode(span, cmds, envp)))
				_path_cat(envp, cmds);
		}

		if (flag)
		{
			execve(*cmds, cmds, envp);
			err_msg = _generate_error(cmds, av, counter);
			perror(err_msg);
		}
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

/*
 * chose_mode - chose the execution mode
 */
int choose_mode(int span, char **cmds, char **envp)
{
	int i = 0;
	_built builtins[] =
	{{"cd", cd_cmd}, {"$$", print_pid},{"$?", print_err},{NULL, NULL},};
	/*{"env", (void(*)(void **))print_envp},
	 * remember to fix protos for this after checking with red*/
		/* {"setenv", (void(*)(void **))_setenv_cmd},
		 * {"unsetenv", (void(*)(void **))_unsetenv}, */
		/* {"alias", (void(*)(void **))alias} */
	for (i = 0; builtins[i].cmd; i++)
	{
		if (!strcmp(*cmds, builtins[i].cmd))
		{
			switch (i)
			{
				case 0:
					cd_cmd(span, cmds, envp);
					return 0;
				case 1:
					print_pid(span, cmds, envp);
					return 0;
				case 2:
					print_err(span, cmds, envp);
					return 0;
				/* case 3: */
				/* 	print_envp(envp, NULL); */
				/* 	return 0; */
				/* case 4: */
				/* 	_setenv_cmd(span, cmds, envp); */
				/* 	return 0; */
				/* case 5: */
				/* 	_unsetenv(cmds[1], envp); */
				/* 	return 0; */
				/* case 6: */
				/* 	alias(cmds, span); */
				/* 	return 0; */
			}
		}
	}
	return 1;
}


